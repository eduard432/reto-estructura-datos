#pragma once
#include "PriorityQueue.h"
#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
void PriorityQueue<T>::enqueue(const T& value, int priority) {
    Node<T>* newNode = new Node(value, priority);
    if(isEmpty() || priority < head->getPriority()) {
        newNode->setNext(head);
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current -> getNext() && current->getNext()->getPriority() <= priority) {
            current = current->getNext();
            
        }

        newNode->setNext(current->getNext());
            current->setNext(newNode);
    }

    count ++;
}

template <typename T>
T PriorityQueue<T>::dequeue() {
    if(isEmpty()) {
        cout << "Empty queue!" << endl;
        throw std::runtime_error("Empty queue!");
    } else {
        Node<T>* temp = head;
        head = temp->getNext();
        T returnValue = temp->getData();
        delete temp;
        --count;
        return returnValue;
    }
}

template <typename T>
T PriorityQueue<T>::peek() const {
    if(isEmpty()) {
        cout << "Empty queue!" << endl;
        throw std::runtime_error("Empty queue!");
    } else {
        T returnValue = head->getData();
        return returnValue;
    }

}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
int PriorityQueue<T>::size() const {
    return count;
}

template <typename T>
void PriorityQueue<T>::print() const {
    if (isEmpty()) {
        cout << "Lista Vacia!" << endl;
    } else {
        const Node<T>* current = head;
        cout << "[";
        while (current) {
            cout << " " << current->getData() << " prio: " << current->getPriority() << " -> ";
            current = current->getNext();
        }
        cout << "]" << endl;
    }
}