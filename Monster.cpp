#include "Monster.h"

float Monster::getHP() const {
    return HP;
}

float Monster::getATK() const {
    return ATK;
}

float Monster::getDEF() const {
    return DEF;
}

string Monster::getName() const {
    return name;
}

void Monster::setHP(const float& health) {
    HP = health;
}

void Monster::setATK(const float& attack) {
    ATK = attack;
}

void Monster::setDEF(const float& defense) {
    DEF = defense;
}

void Monster::setName(const string& n) {
    name = n;
}