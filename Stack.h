#ifndef STACK_H
#define STACK_H

#include "Node.h"

template <typename T>
class Stack {
    private:
        Node<T>* topNode;
        unsigned int count;
    public:
        Stack(): topNode(nullptr), count(0) {}
        ~Stack() {
            while (topNode) {
                Node<T>* tmp = topNode;
                topNode = topNode->getNext();
                delete tmp;
            }
            count = 0;
        }

        void push(const T& v);
        T pop();
        T top();
        bool isEmpty() const;

        void print() const;
};


#include "Stack.tpp"
#endif