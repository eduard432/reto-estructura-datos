#ifndef MONSTER_H
#define MONSTER_H

#include "LinkedList.h"
#include "MonsterAttack.h"
#include "Character.h"
#include <string>

using namespace std;

class Monster: public Character {
    private:
        LinkedList<MonsterAttack> attacks;
    public:
        Monster(const string& n, const float& health = 5, const float& attack = 8, const float& defense = 5 ): Character(n, health, attack, defense) {};
        Monster(): Character() {};

        LinkedList<MonsterAttack>& getAttacks();
        void addAttack(const MonsterAttack& attack);
};

#endif