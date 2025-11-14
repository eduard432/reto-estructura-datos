#pragma once
#include "Board.h"
#include "Utils.h"
#include <iostream>

using namespace std;

void Board::addSquare(const string& name, const float& probability, const bool& visited) {
    Square s = Square(graph.size() + 1, name, probability, visited);
    graph.addVertex(s);
}

bool Board::loadSquareFromCSV(const string& fileName) {
    // TODO;
}

bool Board::isMonsterAttack(const float& probability) {
    double randomProb = Utils().randomNumber();
    return randomProb <= probability;
}

void Board::play() {
    Square square = graph.vertexAt(actualSquareIndex)->getData();
    bool isBattle = isMonsterAttack(square.getProbability());

    if(isBattle) {
        cout << "Estás en batalla" << endl;
    } else {
        cout << "Se evito la batalla" << endl;
    }
}