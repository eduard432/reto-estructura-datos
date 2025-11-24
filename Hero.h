#ifndef HERO_H
#define HERO_H

#include <string>
#include "Character.h"
#include "Attack.h"

using namespace std;

class Hero: public Character {
    private:
        void specialAttack();
        int stamina;
        LinkedList<Attack> attacks;
    public:
        virtual ~Hero() {}
        Hero() : Character() {}
        Hero(const string& n) : Character(n) {}

        int getStamina() const;
        void setStamina(const int& s);

        LinkedList<Attack>& getAttacks();
        void addAttack();
};

#endif