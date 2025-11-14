#ifndef BOARD_H
#define BOARD_H

#include "Graph.h"
#include "Square.h"
#include "LinkedList.h"
#include "Hero.h"
#include <string>

class Board {
    private:
        Graph<Square> graph;
        // LinkedList<> monsters;
        unsigned int actualSquareIndex;
        bool isMonsterAttack(const float& probality);
        Hero hero;
        
    public:
        Board() {
            actualSquareIndex = 0;
        }
        void addSquare(const string& n, const float& p, const bool& v);
        bool loadSquareFromCSV(const string& fileName);
        bool loadMonstersFromCsv(const string& fileName);
        void play();

};

#include "Board.tpp"

#endif