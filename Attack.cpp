#include "Attack.h"

string Attack::getName() const {
    return name;
}

float Attack::getDamage() const {
    return damage;
}

void Attack::setName(const string& n) {
    name = n;
}

void Attack::setDamage(const float& d) {
    damage = d;
}