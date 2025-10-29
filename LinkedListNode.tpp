#include "LinkedListNode.h"


template <typename T>
T LinkedListNode<T>::getData() const {
    return data;
}

template <typename T>
LinkedListNode<T>* LinkedListNode<T>::getPrev() const {
    return prev;
}

template <typename T>
LinkedListNode<T>* LinkedListNode<T>::getNext() const {
    return prev;
}


template <typename T>
void LinkedListNode<T>::setData(const T& val) {
    data = val;
}

template <typename T>
void LinkedListNode<T>::setPrev(const LinkedListNode<T>* node) {
    prev = node;
}

template <typename T>
void LinkedListNode<T>::setNext(const LinkedListNode<T>* node) {
    next = node;
}