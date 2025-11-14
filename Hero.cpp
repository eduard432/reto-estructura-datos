#include "Hero.h"

float Hero::getHP() const {
    return HP;
}

float Hero::getATK() const {
    return ATK;
}

float Hero::getDEF() const {
    return DEF;
}


void Hero::setHP(const float& health) {
    HP = health;
}

void Hero::setATK(const float& attack) {
    ATK = attack;
}

void Hero::setDEF(const float& defense) {
    DEF = defense;
}