#ifndef CLI_H
#define CLI_H

#include "Board.h"

class CLI {
    private:
        Board board;
    public:
    CLI() {
        board.addSquare("Maz_1", 0.8, false);
        board.addSquare("Maz_2", 0.8, false);
        board.connectSquares(0, 1);
        board.addMonster("Monstruo 1", 10, 8, 5);
        board.addMonster("Monstruo 2", 10, 8, 5);
        board.addMonster("Monstruo 3", 10, 8, 5);
    };
    void start();
    bool commands();
    void clear();
};

#endif