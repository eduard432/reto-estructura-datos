#pragma once
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
    bool startMonster = prob >= .5;

    if(startMonster) {
        cout << "El monstruo inicia dando el primer golpe" << endl;
    } else {
        cout << "El jugador da el primer golpe" << endl;
    }
}