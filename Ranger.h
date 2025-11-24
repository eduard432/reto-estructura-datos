#ifndef RANGER_H
#define RANGER_H

#include "Hero.h"

class Ranger: public Hero {
    private:
    public:
        Ranger(const string& n): Hero(n) {}
        string getType() const override { return "Ranger"; }
};

#endif