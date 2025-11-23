#include "Hero.h"


Attack Hero::getSpecialAttack() const {
    return specialAttack;
}

void Hero::setSpecialAttack(const Attack& a) {
    specialAttack = a;
}

int Hero::getStamina() const {
    return stamina;
}

void Hero::setStamina(const int& s){
    stamina = s;
}