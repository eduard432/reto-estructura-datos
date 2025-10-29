#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListNode.h"

template <typename T>
class LinkedList {
	private:
        LinkedListNode<T>* head;
        unsigned int n;
    public:
        LinkedList();
        ~LinkedList();

        unsigned int size() const;
        bool empty() const;

        void clear();
        bool remove(T& value);

        void pushFront(const T& value);
        void pushBack(const T& value);
        bool insert(unsigned int index, const T& value);

        T* elementAt(unsigned int index);

        void print() const;
};


#endif