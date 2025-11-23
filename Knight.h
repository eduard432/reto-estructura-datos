#ifndef KNIGHT_H
#define KNIGHT_H

#include "Hero.h"
#include "Attack.h"

class Knight: public Hero {
    private:
    public:
        Knight(const string& n): Hero(n) {
            Attack specialAttack = Attack("Long sword attack", 6.5);
            setSpecialAttack(specialAttack);
        }
};

#endif