#ifndef MAGE_H
#define MAGE_H

#include "Hero.h"

class Mage: public Hero {
    private:
    public:
        Mage(const string& n): Hero(n) {}
};

#endif