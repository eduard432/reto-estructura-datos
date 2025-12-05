#include "Hero.h"

int Hero::getPower() const {
    return power;
}

void Hero::setPower(const int& p){
    power = p;
}

LinkedList<Attack>& Hero::getAttacks() {
    return attacks;
}

void Hero::addAttack() {
    Attack newAttack = Attack("Ataque 1", 4.0);
    attacks.pushBack(newAttack);
}