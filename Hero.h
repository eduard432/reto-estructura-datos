#ifndef HERO_H
#define HERO_H

#include <string>
#include "Character.h"

using namespace std;

class Hero: public Character {
    private:
    public:
        Hero() : Character() {}
        Hero(const string& n) : Character(n) {}

};

#endif