#ifndef ABILITYTREE_H
#define ABILITYTREE_H

#include "AVL.h"
#include <cmath>
#include "Hero.h"

enum class Attribute {
  DEFENSE,
  HEALTH,
  ATTACK,
  POWER
};

class AbilityTree {
    private:
        AVL<int> tree;
        unsigned int abilities;
        unsigned int defenseIndex;
        unsigned int healthIndex;
        unsigned int attackIndex;
        unsigned int powerIndex;

        bool isPercentage(unsigned int index, unsigned int height) const;
        float calculateUpgrade(unsigned int index, unsigned int height) const;
        void showUpgrade(NodeTree<int>* node);
        void showUpgrades(unsigned int index);
    public:
        AbilityTree(unsigned int height) {
            abilities =  pow(2, height);
            for(unsigned int i = 1; i < abilities; i++)  {
                tree.insert(i);
            }
        };

        bool upgrade(Hero& hero, Attribute type, bool isLeftOption);
        void show();
        void show(Attribute type);

};

#endif