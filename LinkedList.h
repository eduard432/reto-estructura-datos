#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

template <typename T>
class LinkedList {
	private:
        Node<T>* head;
        Node<T>* tail;
        unsigned int n;
    public:
        LinkedList();
        ~LinkedList();

        Node<T>* getHead() const;
        Node<T>* getTail() const;

        Node<T>* search(const T& value) const;

        unsigned int size() const;
        bool isEmpty() const;

        void clear();
        bool remove(const T& val);

        void pushFront(const T& val);
        void pushBack(const T& val);
        bool insert(unsigned int index, const T& val);
        int indexOf(const T& val);

        T elementAt(unsigned int index) const;

        void print() const;

        T& operator[](unsigned int index);
};

#include "LinkedList.tpp"


#endif