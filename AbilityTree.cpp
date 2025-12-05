#include "AbilityTree.h"
#include "NodeTree.h"
#include <iostream>

using namespace std;

bool AbilityTree::upgrade(Hero& hero, Attribute type, bool isLeftOption) {
    int abilityIndex = -1;
    if(type == Attribute::DEFENSE) {
        abilityIndex = defenseIndex;

    } else if(type == Attribute::HEALTH) {
        abilityIndex = healthIndex;
    } else if(type == Attribute::ATTACK) {
        abilityIndex = attackIndex;
    } else if(type == Attribute::POWER) {
        abilityIndex = powerIndex;
    }

    NodeTree<int>* node = tree.search(abilityIndex);
    bool percentage = false;

    if(!node) {
        return false;
    }

    if(isLeftOption) {
        percentage = isPercentage(node->getLeft()->getData(), node->getLeft()->getData());
    } else {
        percentage = isPercentage(node->getRight()->getData(), node->getRight()->getData());
    }


    return true;
}

void AbilityTree::show() {
    cout << "Defense:" << endl;
    show(Attribute::DEFENSE);
    cout << "Health:" << endl;
    show(Attribute::HEALTH);
    cout << "Ataque:" << endl;
    show(Attribute::ATTACK);
    cout << "Power:" << endl;
    show(Attribute::POWER);
}

void AbilityTree::showUpgrade(NodeTree<int>* node) {
    bool percentage = isPercentage(node->getData(), node->getHeight());
    float upgrade = calculateUpgrade(node->getData(), node->getHeight());

    cout << "+" << (percentage ? "%" : "") << upgrade;
}

float AbilityTree::calculateUpgrade(unsigned int index, unsigned int height) const {
    bool percentage = isPercentage(index, height);
    if(height == 0) {
        if (percentage) {
            return 25;
        } else {
            return 80;
        }
    } else if(height == 1) {
        if(percentage) {
            if(percentage) {
                return 50;
            } else {
                return 40;
            }
        }
    } else if(height == 2) {
        return 20;
    } else if(height == 3) {
        return 10;
    }

    return 1;
}

bool AbilityTree::isPercentage(unsigned int index, unsigned int height) const {
    if(height == 0) {
        return index % 4 == 3;
    } else if(height == 1) {
        return index % 8 == 6;
    } else {
        return false;
    }
}

void AbilityTree::showUpgrades(unsigned int index) {
    NodeTree<int>* node = tree.search(index);
    cout << "Habilidad disponibles" << endl;
    if(node->getLeft()) {
        cout << "Opcion 1";
        showUpgrade(node->getLeft());
    }
    if(node->getRight()) {
        cout << "Opcion 2";
        showUpgrade(node->getRight());
    }
}

void AbilityTree::show(Attribute type) {

    switch (type) {
        case Attribute::DEFENSE:
            showUpgrades(defenseIndex);
            break;
        
        case Attribute::HEALTH:
            showUpgrades(healthIndex);
            break;
        
        case Attribute::ATTACK:
            showUpgrades(attackIndex);
            break;
        
        case Attribute::POWER:
            showUpgrades(powerIndex);
            break;
        default:
            break;
    }
}