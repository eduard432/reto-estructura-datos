#ifndef MONSTER_H
#define MONSTER_H

#include <string>

using namespace std;

class Monster: public Character {
    private:

    public:
        Monster(const string& n, const float& health = 100, const float& attack = 8, const float& defense = 5 ) {
            Character(n, health, attack, defense);
        };
        Monster(): Character() {};

};

#endif