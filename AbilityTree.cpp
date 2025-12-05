#include "AbilityTree.h"
#include "NodeTree.h"
#include <iostream>

using namespace std;

bool AbilityTree::upgrade(Hero& hero, Attribute type, bool isLeftOption) {
    unsigned int* currentIndexPtr = nullptr;

    switch (type) {
        case Attribute::DEFENSE: currentIndexPtr = &defenseIndex; break;
        case Attribute::HEALTH:  currentIndexPtr = &healthIndex; break;
        case Attribute::ATTACK:  currentIndexPtr = &attackIndex; break;
        case Attribute::POWER:   currentIndexPtr = &powerIndex; break;
        default: return false;
    }

    int currentIndex = *currentIndexPtr;

    NodeTree<int>* node = tree.search(currentIndex);
    if (!node) return false;

    NodeTree<int>* nextNode = isLeftOption ? node->getLeft() : node->getRight();
    if (!nextNode) return false;

    unsigned int index = nextNode->getData();
    unsigned int height = nextNode->getHeight();

    bool percentage = isPercentage(index, height);

    float amount = calculateUpgrade(index, height);

    switch (type) {
        case Attribute::DEFENSE:
            if (percentage) {
                hero.setDEF(hero.getDEF() * (amount/100));
            }
            else {
                hero.addDEF(amount);
            }
            break;

        case Attribute::HEALTH:
            if (percentage) {
                hero.setHP(hero.getHP() * (amount/100));
            }
            else hero.addHP(amount);
            break;

        case Attribute::ATTACK:
            if (percentage) {
                hero.setATK(hero.getATK() * (amount/100));
            }
            else hero.addATK(amount);
            break;

        case Attribute::POWER:
            if (percentage) {
                hero.setPower(hero.getPower() * (amount/100));
            }
            else hero.addPower(amount);
            break;
    }

    *currentIndexPtr = index;

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