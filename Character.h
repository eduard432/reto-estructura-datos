#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Attack.h"
#include "LinkedList.h"

using namespace std;

class Character  {
    private:
        string name;
        float HP;
        float ATK;
        float DEF;
  
    public:
        Character() : name(""), HP(0), ATK(0), DEF(0) {}
        Character(const string& n, const float& health = 100, const float& attack = 8, const float& defense = 5) : name(n), HP(health), ATK(attack), DEF(defense) {}
        float getHP() const;
        float getATK() const;
        float getDEF() const;
        string getName() const;
        void setHP(const float& health);
        void setATK(const float& attack);
        void setDEF(const float& defense);
        void setName(const string& n);
};

#endif