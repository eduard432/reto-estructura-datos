#ifndef KNIGHT_H
#define KNIGHT_H

#include "Hero.h"
#include "Attack.h"

class Knight: public Hero {
    private:
    public:
        Knight(const string& n): Hero(n) {}
        string getType() const override { return "Knight"; }
};

#endif