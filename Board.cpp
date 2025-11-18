#include "Board.h"
#include "Utils.h"
#include "Monster.h"
#include <iostream>

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

bool Board::loadSquareFromCSV(const string& fileName) {

    return fileName != "";
    // TODO;
}

bool Board::isMonsterAttack(const float& probability) {
    double randomProb = Utils().randomDoubleNumber();
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
    } else {
        cout << "Se evito la batalla" << endl;
    }

    return isBattle;
}

void Board::combat() {
    // Aleatorio quien da el primer golpe:
    double prob = Utils().randomDoubleNumber();
    bool startHero = prob >= .5;
    return combat(startHero);
}

void Board::combat(const bool& heroNextAttack) {
    status = "combat";
    
    if(!heroNextAttack) {
        cout << "El monstruo inicia dando el primer golpe" << endl;
        // Seleccionar un golpe aleatorio del monstruo
        defend();

    } else {
        cout << "El jugador da el primer golpe" << endl;
        attack();
    }
}


void Board::defend() {
    Vector<Attack>& attacks = monsters[actualMonsterIndex].getAttacks();
    int randomAttackIndex = Utils().randomIntNumber(0, attacks.length());

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
        attack();
    }
}

void Board::attack() {
    if(status != "combat") {
        cout << "No estas en combate" << endl;
        return;
    }

    Vector<Attack>& attacks = hero.getAttacks();
    int randomAttackIndex = Utils().randomIntNumber(0, attacks.length());

    cout << "El jugador va atacar con:" << endl;
    cout << "Nombre del ataque: " << attacks[randomAttackIndex].getName() << endl;
    float heroDamage = attacks[randomAttackIndex].getDamage();
    cout << "Daño: " << heroDamage << endl;
    
    float damageMade = Utils().max(1, heroDamage - monsters[actualMonsterIndex].getDEF());
    cout << "Daño inflingido: " << damageMade << endl;

    if(monsters[actualMonsterIndex].getDEF() - damageMade <= 0) {
        // Se murio el monstruo
        cout << "El jugador gano la batalla" << endl;
        status = "peace";
    } else {
        // Guardamos la nueva salud del monstruo
       monsters[actualMonsterIndex].setHP(monsters[actualMonsterIndex].getDEF() - damageMade);

       combat(false);
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
    for (unsigned int i = 0; i < graph.vertexAt(actualSquareIndex)->getEdges().size(); i++) {
        cout << graph.vertexAt(actualSquareIndex)->getEdges()[i]->getData().getName() << ", ";
    }
    cout << "]";
}

void Board::connectSquares(const unsigned int& sq1, const unsigned int& sq2) {
    
    graph.addEdge(graph.vertexAt(sq1)->getData(), graph.vertexAt(sq2)->getData());
}

void Board::showAllSquares() const {
    cout << "[ ";
    for (unsigned int i = 0; i < graph.size(); i++) {
        cout << graph.vertexAt(i)->getData().getName() << ", ";
    }
    cout << "]";
}

int Board::searchSquare(const string& name) const {
    for (unsigned int i = 0; i < graph.size(); i++){
        if(graph.vertexAt(i)->getData().getName() == name) {
            return i;
        }
    }

    return -1;
}

void Board::showActualSquare() const {
    Square sq = graph.vertexAt(actualSquareIndex)->getData();
    cout << "Id: " << sq.getId() << endl;
    cout << "Nombre: " << sq.getName() << endl;
}

void Board::showActualMonster() const {
    if (actualMonsterIndex <= 0) {
        cout << "No hay pelea con algún monstruo" << endl;
        return;
    }
}