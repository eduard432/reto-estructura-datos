#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename T>
class Queue {
    private:
        unsigned int count;
        Node<T>* frontNode;
        Node<T>* backNode;
    public:
        Queue(): count(0), frontNode(nullptr), backNode(nullptr) {}
        ~Queue() {
            while(frontNode) {
                Node<T>* tmp = frontNode;
                frontNode = frontNode->getNext();
                delete tmp;
            }
            count = 0;
        }

        void enqueue(const T& v);
        T dequeue();
        T front();
        bool isEmpty() const;

        void print() const;
};

#include "Queue.tpp"

#endif