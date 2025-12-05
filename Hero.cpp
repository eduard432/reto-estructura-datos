#include "Hero.h"

float Hero::getPower() const {
    return power;
}

void Hero::setPower(float p){
    power = p;
}

LinkedList<Attack>& Hero::getAttacks() {
    return attacks;
}

void Hero::addAttack() {
    Attack newAttack = Attack("Ataque 1", 4.0);
    attacks.pushBack(newAttack);
}

float Hero::addPower(float extraPower) {
    power+=extraPower;
    return power;
}