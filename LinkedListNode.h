#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

template <typename T>
class LinkedListNode {
    private:
        T data;
        LinkedListNode<T>* prev;
        LinkedListNode<T>* next;

    public:
        LinkedListNode(const T& val): data(val), prev(nullptr), next(nullptr) {};

        T getData() const;
        T& getDataRef();
        LinkedListNode<T>* getPrev() const;
        LinkedListNode<T>* getNext() const;

        void setData(const T& val);
        void setPrev(LinkedListNode<T>* node);
        void setNext(LinkedListNode<T>* node);
};

#include "LinkedListNode.tpp"

#endif