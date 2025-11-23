#include "Character.h"
#include "Attack.h"

float Character::getHP() const {
    return HP;
}

float Character::getATK() const {
    return ATK;
}

float Character::getDEF() const {
    return DEF;
}

string Character::getName() const {
    return name;
}


void Character::setHP(const float& health) {
    HP = health;
}

void Character::setATK(const float& attack) {
    ATK = attack;
}

void Character::setDEF(const float& defense) {
    DEF = defense;
}

void Character::setName(const string& n) {
    name = n;
}

LinkedList<Attack>& Character::getAttacks() {
    return attacks;
}

void Character::addAttack() {
    Attack newAttack = Attack("Ataque 1", 4.0);
    attacks.pushBack(newAttack);
}