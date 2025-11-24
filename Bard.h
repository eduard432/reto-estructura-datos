#ifndef BARD_H
#define BARD_H

#include "Hero.h"

class Bard: public Hero {
    private:
    public:
        Bard(const string& n): Hero(n) {}
};

#endif