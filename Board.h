#ifndef BOARD_H
#define BOARD_H

#include "Graph.h"
#include "Square.h"
#include "LinkedList.h"
#include "Hero.h"
#include "Monster.h"
#include <string>

class Board {
    private:
        Graph<Square> graph;
        LinkedList<Monster> monsters;
        unsigned int actualSquareIndex;
        bool isMonsterAttack(const float& probality);
        Hero hero;
        int actualMonsterIndex;
        string status;
        void combat(const bool& heroNextAttack);
        bool isHeroTurn;
        
    public:
        Board() {
            actualSquareIndex = 0;
            hero = Hero("Fulano");
            hero.addAttack();
            actualMonsterIndex = -1;
            status = "peace";
            isHeroTurn = false;
        }
        void addSquare(const string& n, const float& p, const bool& v);
        void connectSquares(const unsigned int& sq1, const unsigned int& sq2);
        void addMonster(const string& name, const float& health = 100, const float& attack = 8, const float& defense = 5 );
        bool loadSquareFromCSV(const string& fileName);
        bool loadMonstersFromCsv(const string& fileName);
        bool play();
        bool getIsInBattle() const;

        void combat();
        void lost();
        string getStatus() const;

        void attack();
        void defend();
        void showSquares() const;
        void showAllSquares() const;
        void showAllMonsters() const;
        int searchSquare(const string& name) const;
        void showActualSquare() const;
        void showActualMonster() const;
        void showHero() const;
        bool changeActualSquare(const unsigned int& square);

};


#endif