#ifndef BOARD_H
#define BOARD_H

#include "Graph.h"
#include "Square.h"
#include "LinkedList.h"
#include "Hero.h"
#include "Monster.h"
#include <string>
#include "AbilityTree.h"

class Board {
    private:
        Graph<Square> graph;
        LinkedList<Monster> monsters;
        unsigned int actualSquareIndex;
        unsigned int startSquareIndex;
        unsigned int treasureSquareIndex;
        unsigned int abilityPoints;
        bool isMonsterAttack(const unsigned int& probality);
        Hero* hero;
        int actualMonsterIndex;

        bool monsterAttacking(MonsterAttack& attack);
        void combatWon();

        string status;

        bool isHeroTurn;
        AbilityTree abilityTree;
        
    public:
        Board() {
            loadMonstersFromCsv("./data/monsters.csv");
            loadSquareFromCsv("./data/squares.csv");
            loadConnectionsFromCsv("./data/connections.csv");
            loadMonsterAttacksFromCsv("./data/monster_attacks.csv");

            startSquareIndex = 0;
            treasureSquareIndex = 7;

            hero = nullptr;
            actualSquareIndex = 0;
            actualMonsterIndex = -1;

            status = "inGame";
            abilityPoints = 0;
        }
        void addSquare(const string& n, const float& p, const bool& v);
        bool connectSquares(const unsigned int& sq1, const unsigned int& sq2);
        void addMonster(const string& name, const float& health = 100, const float& attack = 8, const float& defense = 5 );
        bool addMonsterAttack(const string& monsterName, const MonsterAttack& attack);

        bool loadSquareFromCsv(const string& fileName);
        bool loadMonstersFromCsv(const string& fileName);
        bool loadConnectionsFromCsv(const string& fileName);
        bool loadMonsterAttacksFromCsv(const string& fileName);
        bool play();
        bool getIsInBattle() const;


        void combat();
        void lost();

        void showSquares() const;
        void showAllSquares();
        void showAllMonsters() const;
        int searchSquareByName(const string& name);
        int searchSquareById(const unsigned int& name);
        void showActualSquare() const;
        void showActualMonster() const;
        void showHero() const;
        bool changeActualSquare(const string& squareName);
        void selectHero();

        void showCheatcode();
        Square getActualSquare() const;
        AbilityTree& getAbilityTree();

        unsigned int getAbilityPoints() const;
        void setAbilityPoints(unsigned int newPoints);

        Hero* getHero();

};


#endif