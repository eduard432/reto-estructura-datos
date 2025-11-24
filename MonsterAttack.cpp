#include "MonsterAttack.h"


LinkedList<string>& MonsterAttack::getAnswers() {
    return answers;
}

unsigned int MonsterAttack::getCorrectAnswerI() const {
    return correctAnswerI;
}

void MonsterAttack::addAnswer(const string& name, bool isCorrect) {
    answers.pushBack(name);
    if(isCorrect) {
        correctAnswerI = answers.size() - 1;
    }
}

void MonsterAttack::setCorrectAnswerI(unsigned int index) {
    correctAnswerI = index;
}