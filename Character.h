#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Attack.h"
#include "Vector.h"

using namespace std;

class Character  {
    private:
        string name;
        float HP;
        float ATK;
        float DEF;
        Vector<Attack> attacks;
    public:
        Character() : name(""), HP(0), ATK(0), DEF(0) {}
        Character(const string& n) : name(n), HP(100), ATK(8), DEF(12) {}
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