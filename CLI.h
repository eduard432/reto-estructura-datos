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
    static void readInput(string& value);
    static float readFloatLoop(string prompt);
    static int readIntLoop(string prompt);
    static unsigned int readPositiveIntLoop(string prompt);
    bool requireTokens(const LinkedList<string>& tokens, int count);
};

#endif