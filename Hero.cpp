#include "Hero.h"

int Hero::getStamina() const {
    return stamina;
}

void Hero::setStamina(const int& s){
    stamina = s;
}

LinkedList<Attack>& Hero::getAttacks() {
    return attacks;
}

void Hero::addAttack() {
    Attack newAttack = Attack("Ataque 1", 4.0);
    attacks.pushBack(newAttack);
}