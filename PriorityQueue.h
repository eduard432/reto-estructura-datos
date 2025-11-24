#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "Node.h"

template <typename T>
class PriorityQueue {
    private:
        Node<T>* head;
        int count;
    public:
        PriorityQueue(): head(nullptr), count(0) {};
        ~PriorityQueue() {
            while(head) {
                Node<T>* temp = head;
                head = head->getNext();
                delete temp;
            }
            count = 0;
        }
        void enqueue(const T& value, int priority);
        T dequeue();
        T peek() const;
        bool isEmpty() const;
        int size() const;

        void print() const;

};

#include "PriorityQueue.tpp"

#endif