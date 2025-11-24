#ifndef MONSTER_ATTACK_H
#define MONSTER_ATTACK_H

#include "Attack.h"
#include "LinkedList.h"
#include <string>

class MonsterAttack: public Attack {
    private:
        LinkedList<string> answers;
        unsigned int correctAnswerI;
    public:
        MonsterAttack(const string &n, const float& d): Attack(n, d) {};
        LinkedList<string>& getAnswers();
        unsigned int getCorrectAnswerI () const;

        void addAnswer(const string& answer, bool isCorrect = false);
        void setCorrectAnswerI(unsigned int index); 
};


#endif