#include "LinkedList.h"
#include "LinkedListNode.h"

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    n = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    // Implementar destructor
}

template <typename T>
unsigned int LinkedList<T>::size() const {
    return n;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return n == 0;
}

template <typename T>
void LinkedList<T>::clear() {

}

template <typename T>
bool LinkedList<T>::remove(const T& val) {

}

template <typename T>
void LinkedList<T>::pushFront(const T& val) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(val);
    if(isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
}

template <typename T>
void LinkedList<T>::pushBack(const T& val) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(val);
    if(isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
    }
    n++;
}

template <typename T>
bool LinkedList<T>::insert(unsigned int index, const T& val) {

}