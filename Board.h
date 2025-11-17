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
        
    public:
        Board() {
            actualSquareIndex = 0;
            hero = Hero("Fulano");
            hero.addAttack();
            actualMonsterIndex = -1;
            status = "peace";
        }
        void addSquare(const string& n, const float& p, const bool& v);
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

};

#include "Board.tpp"

#endif