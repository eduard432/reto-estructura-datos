#ifndef CLI_H
#define CLI_H

#include "Board.h"

class CLI {
    private:
        Board board;
    public:
    CLI() {
        board.addSquare("Maz_1", 0.8, true);
        board.addSquare("Maz_2", 0.8, false);
        board.addMonster("Monstruo 1");
        board.addMonster("Monstruo 2");
        board.addMonster("Monstruo 3");
    };
    void start();
    bool commands();
    void clear();
};

#endif