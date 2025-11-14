#pragma once
#include "Stack.h"
#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
void Stack<T>::push(const T& v) {
    Node<T>* newNode = new Node<T>(v);
    newNode->setNext(topNode);
    topNode = newNode;
    ++count;
}

template <typename T>
T Stack<T>::pop() {
    if(isEmpty()) {
        cout << "Empty stack!" << endl;
        throw std::runtime_error("Empty stack!");
    } else {
        Node<T>* temp = topNode;
        topNode = topNode->getNext();
        T returnValue = temp->getData();
        delete temp;
        --count;
        return returnValue;
    }
}

template <typename T>
T Stack<T>::top() {
    if(isEmpty()) {
        cout << "Empty stack!" << endl;
    } else {
         return topNode->getData();
    }
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return count == 0;
}


template <typename T>
void Stack<T>::print() const {
    if (isEmpty()) {
        cout << "Lista Vacia!" << endl;
    } else {
        const Node<T>* current = topNode;
        cout << "[";
        while (current) {
            cout << " " << current->getData() << " ->";
            current = current->getNext();
        }
        cout << "]" << endl;
    }
}