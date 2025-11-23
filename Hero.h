#ifndef HERO_H
#define HERO_H

#include <string>
#include "Character.h"
#include "Attack.h"

using namespace std;

class Hero: public Character {
    private:
        Attack specialAttack;
        int stamina;
    public:
        Hero() : Character() {}
        Hero(const string& n) : Character(n) {}
        Attack getSpecialAttack() const;
        void setSpecialAttack(const Attack& a);

        int getStamina() const;
        void setStamina(const int& s);
};

#endif