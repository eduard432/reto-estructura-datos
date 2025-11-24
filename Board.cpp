#include "Board.h"
#include "Utils.h"
#include "Monster.h"

#include "Knight.h"

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
    m.addAttack();
    monsters.pushBack(m);
}

bool Board::isMonsterAttack(const unsigned int& probability) {
    unsigned int randomProb = Utils().randomIntNumber(0, 10);
    return randomProb <= probability;
}

bool Board::getIsInBattle() const {
    return actualMonsterIndex >= 0;
}

bool Board::play() {
    Square square = graph.vertexAt(actualSquareIndex)->getData();
    bool isBattle = isMonsterAttack(square.getProbability());

    if(isBattle) {
        cout << "Estás en batalla" << endl;
        int selectedMonsterI = Utils().randomIntNumber(0, monsters.size());
        Monster& selectedMonster = monsters[selectedMonsterI];
        cout << "Pelearas contra: " << selectedMonster.getName() << endl;
        actualMonsterIndex = selectedMonsterI;
        status = "inAttack";
    } else {
        cout << "Se evito la batalla" << endl;
        // Marcamos como visitada la casilla
        graph.vertexAt(actualSquareIndex)->getData().setVisited(true);
    }

    return isBattle;
}

void Board::combat() {
    if(status != "inAttack" && status != "combat") {
        cout << "Actualmente no estás siendo atacado por un monstruo" << endl;
        return;
    }
    if(status == "inAttack") {
        double prob = Utils().randomDoubleNumber();
        bool startHero = prob >= .5;
        isHeroTurn = startHero;
    }
    // Aleatorio quien da el primer golpe:
    return combat(isHeroTurn);
}

void Board::combat(const bool& heroNextAttack) {
    status = "combat";
    
    if(!heroNextAttack) {
        cout << "El monstruo ataca" << endl;
        defend();

    } else {
        cout << "El jugador da un golpe" << endl;
        attack();
    }
}


void Board::defend() {
    // Seleccionar un golpe aleatorio del monstruo
    LinkedList<Attack>& attacks = monsters[actualMonsterIndex].getAttacks();
    int randomAttackIndex = Utils().randomIntNumber(0, attacks.size() - 1);

    cout << "El monstruo va atacar con:" << endl;
    cout << "Nombre del ataque: " << attacks[randomAttackIndex].getName() << endl;
    float monsterDamage = attacks[randomAttackIndex].getDamage();
    cout << "Daño: " << monsterDamage << endl;
    
    float givenDamage = Utils().max(1, monsterDamage - hero.getDEF());
    cout << "Daño recibido: " << givenDamage << endl;

    if(hero.getHP() - givenDamage <= 0) {
        // Se murio el jugador
        lost();
    } else {
        // Guardamos la nueva salud del heroe
        hero.setHP(hero.getHP() - givenDamage);
        isHeroTurn = true;
    }
}

void Board::attack() {
    if(status != "combat") {
        cout << "No estas en combate" << endl;
        return;
    }

    LinkedList<Attack>& attacks = hero.getAttacks();
    int randomAttackIndex = Utils().randomIntNumber(0, attacks.size() - 1);

    cout << "El jugador va atacar con:" << endl;
    cout << "Nombre del ataque: " << attacks[randomAttackIndex].getName() << endl;
    float heroDamage = attacks[randomAttackIndex].getDamage();
    cout << "Daño: " << heroDamage << endl;
    
    float damageMade = Utils().max(1, heroDamage - monsters[actualMonsterIndex].getDEF());
    cout << "Daño inflingido: " << damageMade << endl;

    if((monsters[actualMonsterIndex].getHP() - damageMade) <= 0) {
        // Se murio el monstruo
        cout << "El jugador gano la batalla" << endl;
        status = "peace";
        // Actualizamos la casilla actual como visitada
        graph.vertexAt(actualSquareIndex)->getData().setVisited(true);
        // No hay monstruo actual
        actualMonsterIndex = -1;
    } else {
        // Guardamos la nueva salud del monstruo
        monsters[actualMonsterIndex].setHP(monsters[actualMonsterIndex].getHP() - damageMade);
        isHeroTurn = false;
    }

}

void Board::lost() {
    status = "lost";
    cout << "El jugador perdió la pertida" << endl;
}

string Board::getStatus() const {
    return status;
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

void Board::showAllSquares() const {
    cout << "[ ";
    for (unsigned int i = 0; i < graph.size(); i++) {
        cout << graph.vertexAt(i)->getData().getName() << ", ";
    }
    cout << "]";
}

void Board::showAllMonsters() const {
    cout << "[ ";
    for (unsigned int i = 0; i < monsters.size(); i++) {
        cout << monsters.elementAt(i).getName() << ", ";
    }
    cout << "]";
}

int Board::searchSquareByName(const string& name) const {
    for (unsigned int i = 0; i < graph.size(); i++){
        if(graph.vertexAt(i)->getData().getName() == name) {
            return i;
        }
    }

    return -1;
}

int Board::searchSquareById(const unsigned int& id) const {
    for (unsigned int i = 0; i < graph.size(); i++){
        if(graph.vertexAt(i)->getData().getId() == id) {
            return i;
        }
    }

    return -1;
}

void Board::showActualSquare() const {
    Square sq = graph.vertexAt(actualSquareIndex)->getData();
    cout << "Id: " << sq.getId() << endl;
    cout << "Nombre: " << sq.getName() << endl;
    cout << "¿Casilla superada? " << (sq.getVisited() ? "Sí" : "No") << endl;
}

void Board::showActualMonster() const {
    if (actualMonsterIndex < 0) {
        cout << "No hay pelea con algún monstruo" << endl;
    } else {
        Monster monster = monsters.elementAt(actualMonsterIndex);
        cout << "Nombre: " << monster.getName() << endl;
        cout << "ATK: " << monster.getATK() << endl;
        cout << "HP: " << monster.getHP() << endl;
        cout << "DEF: " << monster.getDEF() << endl;
    }
}

void Board::showHero() const {
    cout << "Nombre: " << hero.getName() << endl;
    cout << "ATK: " << hero.getATK() << endl;
    cout << "HP: " << hero.getHP() << endl;
    cout << "DEF: " << hero.getDEF() << endl;
}

bool Board::changeActualSquare(const string& squareName) {


    // TODO change to searchSquareById;
    int sIndex = searchSquareByName(squareName);

    if(sIndex == -1) {
        cout << "No existe esa casilla" << endl;
        return false;
    }

    actualSquareIndex = sIndex;

    return true;
}

Square Board::getActualSquare() const {
    return graph.vertexAt(actualSquareIndex)->getData();
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

        // Verificamos que sea del tamaño correcto
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

        // Verificamos que sea del tamaño correcto
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

        // Verificamos que sea del tamaño correcto
        if(row.size() != 2) return false;


        unsigned int id1 = static_cast<unsigned int>(stoul(row.elementAt(0)));
        unsigned int id2 = static_cast<unsigned int>(stoul(row.elementAt(1)));

        connectSquares(id1, id2);
    }

    file.close();
    return true;
}

void Board::showCheatcode() {
    LinkedList<Square> path = graph.dijkstraPath(graph.getVertices().elementAt(startSquareIndex)->getData(), graph.getVertices().elementAt(treasureSquareIndex)->getData());
    graph.dijkstraPrint(graph.getVertices().elementAt(startSquareIndex)->getData());
    Node<Square>* current = path.getHead();

    while(current) {
        std::cout << current->getData().getName();

        current = current->getNext();
        if(current) {
            cout << "->";
        }
    }
}

// void Board::selectCharacter() {
//     string name;
//     int characterChosen;

//     cout << "Escribe el nombre de tu heroe: ";
//     cin >> name;

//     cout << "Elige tu clase: " << endl;
//     cout << "1. Caballero" << endl;
//     cout << "2. Mago" << endl;
//     cout << "3. Explorador" << endl;
//     cout << "4. Bard" << endl;
//     cout << "Ingresa tu opción (1-4): ";
//     cin >> characterChosen;


//     switch(characterChosen){
//         case 1:
//             hero = new Knight(name);
//         case 2:
//             return new Mage(name);
//         case 3:
//             return new Ranger(name);
//         case 4:
//             return new Bard(name);
//         default:
//             cout << "Opción inválida, defaulting to Knight.\n";
//             return new Knight(name);
//     }
// }