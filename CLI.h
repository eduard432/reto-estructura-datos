#ifndef CLI_H
#define CLI_H

#include "Board.h"

class CLI {
    private:
        Board board;
    public:
    CLI() {};
    void start();
    bool commands();
    void clear();
    void readInput(string& value);
};

#endif