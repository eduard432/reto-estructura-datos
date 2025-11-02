#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListNode.h"

template <typename T>
class LinkedList {
	private:
        LinkedListNode<T>* head;
        LinkedListNode<T>* tail;
        unsigned int n;
    public:
        LinkedList();
        ~LinkedList();

        LinkedListNode<T>* getHead() const;
        LinkedListNode<T>* getTail() const;

        unsigned int size() const;
        bool isEmpty() const;

        void clear();
        bool remove(const T& val);

        void pushFront(const T& val);
        void pushBack(const T& val);
        bool insert(unsigned int index, const T& val);

        T elementAt(unsigned int index) const;

        void print() const;

        T& operator[](int index);
};

#include "LinkedList.tpp"


#endif