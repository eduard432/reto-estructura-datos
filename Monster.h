#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Attack.h"
#include "Vector.h"

using namespace std;

class Monster {
    private:
        float HP;
        float ATK;
        float DEF;
        string name;
        Vector<Attack> attacks;
    public:
        Monster(const string& n, const float& health = 100, const float& attack = 8, const float& defense = 5 ) {
            name = n;
            HP = health;
            ATK = attack;
            DEF = defense;
        }
        float getHP() const;
        float getATK() const;
        float getDEF() const;
        string getName() const;
        void setHP(const float& health);
        void setATK(const float& attack);
        void setDEF(const float& defense);
        void setName(const string& n);
        Vector<Attack>& getAttacks();
        void addAttack();

};

#endif