#include "Monster.h"

LinkedList<MonsterAttack>& Monster::getAttacks() {
    return attacks;
}

void Monster::addAttack(const MonsterAttack& attack) {
    attacks.pushBack(attack);
}