#pragma once

#include "LinkedList.h"
#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    n = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
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
    if (isEmpty()) return;

    Node<T>* current = head;
    while (current) {
        Node<T>* aux = current->getNext();
        delete current;
        current = aux;
    }

    head = nullptr;
    tail = nullptr;
    n = 0;
}

template <typename T>
bool LinkedList<T>::remove(const T& val) {
    if (isEmpty()) return false;

    Node<T>* temp = nullptr;

    if (head->getData() == val) {
        temp = head;
        head = head->getNext();
        if (head) head->setPrev(nullptr);
        else tail = nullptr;
        delete temp;
        n--;
        return true;
    }

    Node<T>* current = head;
    while (current->getNext()) {
        if (current->getNext()->getData() == val) {
            temp = current->getNext();
            current->setNext(temp->getNext());
            if (temp->getNext()) temp->getNext()->setPrev(current);
            else tail = current;
            delete temp;
            n--;
            return true;
        }
        current = current->getNext();
    }

    return false;
}

template <typename T>
void LinkedList<T>::pushFront(const T& val) {
    Node<T>* newNode = new Node<T>(val);

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }

    n++;
}

template <typename T>
void LinkedList<T>::pushBack(const T& val) {
    Node<T>* newNode = new Node<T>(val);

    if (isEmpty()) {
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
    if (index > n) return false;
    if (index == 0) {
        pushFront(val);
        return true;
    }
    if (index == n) {
        pushBack(val);
        return true;
    }

    Node<T>* current = head;
    for (unsigned int i = 0; i < index - 1; i++) {
        current = current->getNext();
    }

    Node<T>* newNode = new Node<T>(val);
    newNode->setNext(current->getNext());
    newNode->setPrev(current);
    current->getNext()->setPrev(newNode);
    current->setNext(newNode);

    n++;
    return true;
}

template <typename T>
void LinkedList<T>::print() const {
    if (isEmpty()) {
        cout << "Lista vacía" << endl;
        return;
    }

    Node<T>* current = head;
    while (current) {
        cout << current->getData();
        if (current->getNext()) cout << " -> ";
        current = current->getNext();
    }
    cout << endl;
}


template <typename T>
T LinkedList<T>::elementAt(unsigned int index) const {
    if (isEmpty() || index >= n) {
        return T();
    }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->getNext();
    }

    return current->getData();
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (isEmpty() || index >= n) {
        throw "Índice fuera del rango";
    }

    Node<T>* current = head;
    for (unsigned int i = 0; i < index; i++) {
        current = current->getNext();
    }

    return current->getDataRef();
}

template <typename T>
Node<T>* LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail() const {
    return tail;
}