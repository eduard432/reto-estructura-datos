#ifndef HERO_H
#define HERO_H

#include <string>
#include "Character.h"
#include "Attack.h"

using namespace std;

class Hero: public Character {
    private:
        void specialAttack();
        int power;
        LinkedList<Attack> attacks;
    public:
        virtual ~Hero() {}
        virtual string getType() const = 0;
        Hero() : Character() {}
        Hero(const string& n) : Character(n) {}

        int getPower() const;
        void setPower(const int& p);

        LinkedList<Attack>& getAttacks();
        void addAttack();
};

#endif