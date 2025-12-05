#include "Board.h"
#include "Utils.h"
#include "CLI.h"
#include "Monster.h"
#include "MonsterAttack.h"

#include "Knight.h"
#include "Mage.h"
#include "Ranger.h"
#include "Bard.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void Board::addSquare(const string& name, const float& probability, const bool& visited) {
    Square s = Square(graph.size() + 1, name, probability, visited);
    graph.addVertex(s);
}

void Board::addMonster(const string& name, const float& health, const float& attack, const float& defense ) {
    Monster m = Monster(name, health, attack, defense);
    monsters.pushBack(m);
}

bool Board::isMonsterAttack(const unsigned int& probability) {
    unsigned int randomProb = Utils().randomIntNumber(0, 10);
    return randomProb <= probability;
}

bool Board::getIsInBattle() const {
    return actualMonsterIndex != -1;
}

bool Board::play() {

    if(hero == nullptr) {
        cout << "Selecciona un heroe antes de jugar" << endl;
        cout << "Tip, usa /register" << endl;
        return false;
    }

    if(status == "won" || status == "lost") {
        cout << "Ya ganaste, ¿Para que quieres seguir jugando?" << endl;

        return false;
    }

    if(actualMonsterIndex != -1) {
        cout << "Ya estas en combate, usa el comando /combat" << endl;
        return false;
    }

    Square square = graph.vertexAt(actualSquareIndex)->getData();
    bool isBattle = isMonsterAttack(square.getProbability());

    if(isBattle) {
        cout << "Estas en batalla" << endl;
        int selectedMonsterI = Utils().randomIntNumber(0, monsters.size());
        Monster& selectedMonster = monsters[selectedMonsterI];
        cout << "Pelearas contra: " << selectedMonster.getName() << endl;
        actualMonsterIndex = selectedMonsterI;
    } else {
        cout << "Se evito la batalla" << endl;
        // Marcamos como visitada la casilla
        graph.vertexAt(actualSquareIndex)->getData().setVisited(true);
    }

    return isBattle;
}


void Board::combatWon() {
    cout << "El jugador gano la batalla" << endl;
    // Actualizamos la casilla actual como visitada
    graph.vertexAt(actualSquareIndex)->getData().setVisited(true);
    // No hay monstruo actual
    actualMonsterIndex = -1;
}

bool Board::monsterAttacking(MonsterAttack& attack) {
    cout << "Pregunta: " << attack.getName() << endl;

    Node<string>* current = attack.getAnswers().getHead();
    int i = 0;

    while (current) {
        cout << "[" << i << "] " << current->getData() << endl;
        current = current->getNext();
        i++;
    }

    unsigned int answer;
    do {
        answer = CLI::readPositiveIntLoop("Tu respuesta: ");
    } while (answer >= attack.getAnswers().size());

    return answer == attack.getCorrectAnswerI();
}



void Board::combat() {
    if(hero == nullptr) {
        cout << "Registrate antes del combate" << endl;
        return;
    }

    if(actualMonsterIndex == -1) {
        cout << "Actualmente no estas en un combate" << endl;
        return;
    }
    
    // Seleccionamos un ataque aleatorio del monstruo
    LinkedList<MonsterAttack>& attacks = monsters[actualMonsterIndex].getAttacks();
    
    if (attacks.size() == 0) {
        cout << "El monstruo actual no tiene ataques" << endl;
        
        combatWon();
        
        return;
    }
    
    int randomAttackIndex = Utils().randomIntNumber(0, attacks.size() - 1);

    cout << randomAttackIndex << endl;
    
    MonsterAttack mnstrAttack = attacks[randomAttackIndex];
    
    cout << "El monstruo va atacar con: " << endl;
    bool isDefended = monsterAttacking(mnstrAttack);

    if(!isDefended) {
        // TODO: usar el multiplicador de dificultad
        cout << "Respuesta incorrecta, recibiras dano" << endl;
        float monsterDamage = mnstrAttack.getDamage();
        cout << "Dano: " << monsterDamage << endl;
        
        float givenDamage = Utils().max(1, monsterDamage - hero->getDEF());
        cout << "Dano recibido: " << givenDamage << endl;

        if(hero->getHP() - givenDamage <= 0) {
            // Se murio el jugador
            lost();
            return;
        } else {
            // Guardamos la nueva salud del heroe
            hero->setHP(hero->getHP() - givenDamage);
        }
    }

    cout << "Turno del jugador, selecciona un ataque:" << endl;
    Node<Attack>* current = hero->getAttacks().getHead();

    int i = 0;
    while(current) {
        cout << "[" << i << "] " << current->getData().getName() << endl;
        current = current->getNext();
        i++;
    }

    unsigned int selectedAttack;

    do {
        selectedAttack = CLI::readPositiveIntLoop("Tu respuesta: ");

    } while (selectedAttack >= hero->getAttacks().size());
    

    Attack heroAttack = hero->getAttacks()[selectedAttack];

    cout << "Nombre del ataque: " << heroAttack.getName() << endl;
    float heroDamage = heroAttack.getDamage();
    cout << "Dano: " << heroDamage << endl;
    
    float damageMade = Utils().max(1, heroDamage - monsters[actualMonsterIndex].getDEF());
    cout << "Dano inflingido: " << damageMade << endl;

    if((monsters[actualMonsterIndex].getHP() - damageMade) <= 0) {
        // Se murio el monstruo
        cout << "El jugador gano la batalla" << endl;
        // Actualizamos la casilla actual como visitada
        graph.vertexAt(actualSquareIndex)->getData().setVisited(true);
        // No hay monstruo actual
        actualMonsterIndex = -1;
    } else {
        // Guardamos la nueva salud del monstruo
        monsters[actualMonsterIndex].setHP(monsters[actualMonsterIndex].getHP() - damageMade);
    }

}

void Board::lost() {
    cout << "El jugador perdio la pertida" << endl;
    status = "lost";
}

void Board::showSquares() const {
    cout << "[ ";
    Node<Edge<Square>>* current = graph.vertexAt(actualSquareIndex)->getEdges().getHead();
    while(current) {
        cout << current->getData().getVertex()->getData().getName() << ", ";
        current = current->getNext();
    }
    cout << "]";
}

bool Board::connectSquares(const unsigned int& sq1, const unsigned int& sq2) {
    Square& square1 = graph.vertexAt(searchSquareById(sq1))->getData();
    Square& square2 = graph.vertexAt(searchSquareById(sq2))->getData();

    unsigned int weight = (square1.getProbability() + square2.getProbability()) / 2;

    graph.addEdge(square1, square2, weight);
    return true;
}

void Board::showAllSquares() {
    cout << "[ ";

    Node<Vertex<Square>*>* current = graph.getVertices().getHead();
    while(current) {
        cout << current->getData()->getData().getName() << ", ";
        current = current->getNext();
    }
    cout << "]";
}

void Board::showAllMonsters() const {
    cout << "[ ";
    Node<Monster>* current = monsters.getHead();
    while(current) {
        cout << current->getData().getName() << ", ";
        current = current->getNext();
    }
    cout << "]";
}

int Board::searchSquareByName(const string& name) {
    Node<Vertex<Square>*>* current = graph.getVertices().getHead();
    int count = 0;
    while(current) {
        if(current->getData()->getData().getName() == name) {
            return count;
        }
        current = current->getNext();
        count++;
    }

    return -1;
}

int Board::searchSquareById(const unsigned int& id) {
    Node<Vertex<Square>*>* current = graph.getVertices().getHead();
    int count = 0;
    while(current) {
        if(current->getData()->getData().getId() == id) {
            return count;
        }
        current = current->getNext();
        count++;
    }

    return -1;
}

void Board::showActualSquare() const {
    Square sq = graph.vertexAt(actualSquareIndex)->getData();
    cout << "Id: " << sq.getId() << endl;
    cout << "Nombre: " << sq.getName() << endl;
    cout << "¿Casilla superada? " << (sq.getVisited() ? "Si" : "No") << endl;
}

void Board::showActualMonster() const {
    if (actualMonsterIndex < 0) {
        cout << "No hay pelea con algun monstruo" << endl;
    } else {
        Monster monster = monsters.elementAt(actualMonsterIndex);
        cout << "Nombre: " << monster.getName() << endl;
        cout << "ATK: " << monster.getATK() << endl;
        cout << "HP: " << monster.getHP() << endl;
        cout << "DEF: " << monster.getDEF() << endl;
    }
}

void Board::showHero() const {
    cout << "Nombre: " << hero->getName() << endl;
    cout << "ATK: " << hero->getATK() << endl;
    cout << "HP: " << hero->getHP() << endl;
    cout << "DEF: " << hero->getDEF() << endl;
    cout << "Tipo: " << hero->getType() << endl;
}

bool Board::changeActualSquare(const string& squareName) {
    // TODO change to searchSquareById;
    int sIndex = searchSquareByName(squareName);

    if(sIndex == -1) {
        cout << "No existe esa casilla" << endl;
        return false;
    }

    if(actualSquareIndex == static_cast<unsigned int>(sIndex)) {
        cout << "Ya estas en la casilla" << endl;

        return false;
    }

    if(treasureSquareIndex == static_cast<unsigned int>(sIndex)) {
        cout << "Ganaste el juego" << endl;
        status = "won";
    }

    actualSquareIndex = sIndex;

    return true;
}

Square Board::getActualSquare() const {
    return graph.vertexAt(actualSquareIndex)->getData();
}

bool Board::addMonsterAttack(const string& monsterName, const MonsterAttack& attack) {
    Node<Monster>* current = monsters.getHead();

    while(current) {
        if(current->getData().getName() == monsterName) {
            current->getDataRef().addAttack(attack);
            return true;
        }

        current = current->getNext();
    }

    return false;
}

bool Board::loadMonstersFromCsv(const string& fileName) {
    ifstream file(fileName);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return false;
    }

    string line;

    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo: " << fileName << endl;

    while(getline(file, line)) {
        stringstream ss(line);
        string cell;
        LinkedList<string> row;
        
        while(getline(ss, cell, ',')) {
            if(cell.length() == 0) return false;
            row.pushBack(cell);
        }

        // Verificamos que sea del tamano correcto
        if(row.size() != 4) return false;

        string name = row.elementAt(0);
        float health = stof(row.elementAt(1));
        float attack = stof(row.elementAt(2));
        float defense = stof(row.elementAt(3));

        addMonster(name, health, attack, defense);
    }

    file.close();
    return true;
}

bool Board::loadSquareFromCsv(const string& fileName) {
    ifstream file(fileName);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return false;
    }

    string line;

    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo: " << fileName << endl;

    while(getline(file, line)) {
        stringstream ss(line);
        string cell;
        LinkedList<string> row;
        
        while(getline(ss, cell, ',')) {
            if(cell.length() == 0) return false;
            row.pushBack(cell);
        }

        // Verificamos que sea del tamano correcto
        if(row.size() != 3) return false;

        string name = row.elementAt(0);
        unsigned int probability = static_cast<unsigned int>(stoul(row.elementAt(1)));
        bool visited = (row.elementAt(2) == "true");

        addSquare(name, probability, visited);
    }

    file.close();
    return true;
}

bool Board::loadConnectionsFromCsv(const string& fileName) {
    ifstream file(fileName);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return false;
    }

    string line;

    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo: " << fileName << endl;

    while(getline(file, line)) {
        LinkedList<string> row = Utils().split(line, ',');

        // Verificamos que sea del tamano correcto
        if(row.size() != 2) return false;


        unsigned int id1 = static_cast<unsigned int>(stoul(row.elementAt(0)));
        unsigned int id2 = static_cast<unsigned int>(stoul(row.elementAt(1)));

        connectSquares(id1, id2);
    }

    file.close();
    return true;
}

bool Board::loadMonsterAttacksFromCsv(const string& fileName) {
    ifstream file(fileName);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return false;
    }

    string line;

    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo: " << fileName << endl;

    while(getline(file, line)) {
        stringstream ss(line);
        string cell;
        LinkedList<string> row;
        
        // Parseo CSV
        while(getline(ss, cell, ',')) {
            if(cell.length() == 0) continue;
            row.pushBack(cell);
        }

        // Cada fila debe tener exactamente 7 valores
        if(row.size() != 7) {
            cerr << "Fila ignorada por tamaño incorrecto: " << line << endl;
            continue;
        }

        try {
            string monsterName = row.elementAt(0);
            string name = row.elementAt(1);

            float damage = std::stof(row.elementAt(2));

            unsigned int correctAnswer =
                static_cast<unsigned int>(std::stoul(row.elementAt(6)));

            // Validación rango
            if(correctAnswer > 3) {
                cerr << "Fila ignorada: correctAnswer fuera de rango -> "
                     << row.elementAt(6) << endl;
                continue;
            }

            // Crear ataque
            MonsterAttack attack(name, damage);

            for(unsigned int i = 3; i <= 5; i++) {
                string answer = row.elementAt(i);
                bool isCorrect = (i - 2 == correctAnswer);
                attack.addAnswer(answer, isCorrect);
            }

            bool isAdded = addMonsterAttack(monsterName, attack);

            if(!isAdded) {
                cout << "No se pudo agregar el ataque: " << name << endl;
                continue;
            }

        }
        catch(const std::invalid_argument& e) {
            cerr << "Error: valor no numérico en CSV. Línea: " << line << endl;
            cerr << "Detalle: " << e.what() << endl;
            continue;
        }
        catch(const std::out_of_range& e) {
            cerr << "Error: número fuera de rango en CSV. Línea: " << line << endl;
            cerr << "Detalle: " << e.what() << endl;
            continue;
        }
        catch(...) {
            cerr << "Error desconocido procesando la línea: " << line << endl;
            continue;
        }
    }

    file.close();
    return true;
}


void Board::showCheatcode() {
    LinkedList<Square> path = graph.dijkstraPath(graph.getVertices().elementAt(startSquareIndex)->getData(), graph.getVertices().elementAt(treasureSquareIndex)->getData());
    Node<Square>* current = path.getHead();

    while(current) {
        std::cout << current->getData().getName();

        current = current->getNext();
        if(current) {
            cout << "->";
        }
    }
}

void Board::selectHero() {
    if (hero != nullptr) {
        cout << "Ya te registraste" << endl;
        return;
    }

    string name;

    cout << "Escribe el nombre de tu heroe: ";
    CLI::readInput(name);
    cout << endl;

    cout << "Elige tu clase: " << endl;
    cout << "1. Caballero" << endl;
    cout << "2. Mago" << endl;
    cout << "3. Explorador" << endl;
    cout << "4. Bard" << endl;

    unsigned int characterChosen;

    do {
        characterChosen = CLI::readPositiveIntLoop("Ingresa tu opción (1-4): ");

        if (characterChosen == 0 || characterChosen > 4) {
            cout << "Opción inválida. Intenta nuevamente." << endl;
        }

    } while (characterChosen == 0 || characterChosen > 4);

    // Crear héroe
    switch (characterChosen) {
        case 1: hero = new Knight(name); break;
        case 2: hero = new Mage(name); break;
        case 3: hero = new Ranger(name); break;
        case 4: hero = new Bard(name); break;
    }

    hero->addAttack();
}
