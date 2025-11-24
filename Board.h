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
        unsigned int startSquareIndex;
        unsigned int treasureSquareIndex;
        bool isMonsterAttack(const unsigned int& probality);
        Hero hero;
        int actualMonsterIndex;
        string status;
        void combat(const bool& heroNextAttack);
        bool isHeroTurn;
        
    public:
        Board() {
            loadMonstersFromCsv("./data/monsters.csv");
            loadSquareFromCsv("./data/squares.csv");
            loadConnectionsFromCsv("./data/connections.csv");

            startSquareIndex = 0;
            treasureSquareIndex = 7;

            actualSquareIndex = 0;
            hero = Hero("Fulano");
            hero.addAttack();
            actualMonsterIndex = -1;
            status = "peace";
            isHeroTurn = false;
        }
        void addSquare(const string& n, const float& p, const bool& v);
        bool connectSquares(const unsigned int& sq1, const unsigned int& sq2);
        void addMonster(const string& name, const float& health = 100, const float& attack = 8, const float& defense = 5 );
        bool loadSquareFromCsv(const string& fileName);
        bool loadMonstersFromCsv(const string& fileName);
        bool loadConnectionsFromCsv(const string& fileName);
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
        int searchSquareByName(const string& name) const;
        int searchSquareById(const unsigned int& name) const;
        void showActualSquare() const;
        void showActualMonster() const;
        void showHero() const;
        bool changeActualSquare(const string& squareName);
        void selectCharacter();

        void showCheatcode();
        Square getActualSquare() const;

};


#endif