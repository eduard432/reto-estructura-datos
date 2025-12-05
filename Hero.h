#ifndef HERO_H
#define HERO_H

#include <string>
#include "Character.h"
#include "Attack.h"

using namespace std;

class Hero: public Character {
    private:
        void specialAttack();
        float power;
        LinkedList<Attack> attacks;
    public:
        virtual ~Hero() {}
        virtual string getType() const = 0;
        Hero() : Character() {
            power = 0;
        }
        Hero(const string& n) : Character(n) {}

        float getPower() const;
        void setPower(float p);
        float addPower(float extrPower);

        LinkedList<Attack>& getAttacks();
        void addAttack();
};

#endif