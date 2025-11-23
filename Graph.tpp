#pragma once
#include <iostream>

#include "Vertex.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "Graph.h"

template <typename T>
void Graph<T>::resetVisited() {
    Node<Vertex<T>*>* current = vertices.getHead();

    while(current) {
        current->getData()->setVisited(false);
        current = current->getNext();
    }
}

template <typename T>
int Graph<T>::indexOf(const T& data) {
    Node<Vertex<T>*>* current = vertices.getHead();
    int count = 0;

    while(current) {
        if(current->getData()->getData() == data) {
            return count;
        }
        current = current->getNext();
        count++;
    }
    return -1;
}

template <typename T>
Vertex<T>* Graph<T>::vertexAt(const unsigned int i) const {
    return vertices.elementAt(i);
}

template <typename T>
bool Graph<T>::addVertex(const T& data) {
    // Ya existe
    if(indexOf(data) != -1) {
        return false;
    }

    Vertex<T>* v = new Vertex<T>(data);
    v->setIndex(vertices.size());
    vertices.pushBack(v);

    return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& v, const T& u) {
    
    int vIndex = indexOf(v);
    int uIndex = indexOf(u);
    
    if(vIndex == -1 || uIndex == -1) {
        return false;
    }

    vertices[vIndex]->addEdge(vertices[uIndex]);
    vertices[uIndex]->addEdge(vertices[vIndex]);

    return true;
}

template <typename T>
LinkedList<Vertex<T>*>& Graph<T>::getVertices() { return vertices; }

template <typename T>
void Graph<T>::BFS(const T& start) {
    int startIndex = indexOf(start);
    if (startIndex == -1) {
        std::cout << "Initial node not found" << std::endl;
        return;
    }

    resetVisited();
    Queue<int> queue;

    vertices[startIndex]->setVisited(true);
    queue.enqueue(startIndex);

    while (!queue.isEmpty()) {
        int index = queue.dequeue();
        std::cout << vertices[index]->getData() << "->";

        Node<Vertex<T>*>* current = vertices[index]->getEdges().getHead();
        while (current) {

            Vertex<T>* neighbor = current->getData();

            if (!neighbor->getVisited()) {
                neighbor->setVisited(true);
                queue.enqueue(neighbor->getIndex());
            }

            current = current->getNext();
        }
    }

    std::cout << std::endl;
}


template <typename T>
void Graph<T>::DFS(const T& start) {
    int startIndex = indexOf(start);
    if (startIndex == -1) {
        std::cout << "Initial node not found" << std::endl;
        return;
    }

    resetVisited();
    Stack<int> stack;

    vertices[startIndex]->setVisited(true);
    stack.push(startIndex);

    while (!stack.isEmpty()) {
        int index = stack.pop();
        std::cout << vertices[index]->getData() << "->";

        Node<Vertex<T>*>* current = vertices[index]->getEdges().getHead();
        while (current) {

            Vertex<T>* neighbor = current->getData();

            if (!neighbor->getVisited()) {
                neighbor->setVisited(true);
                stack.push(neighbor->getIndex());
            }

            current = current->getNext();
        }
    }

    std::cout << std::endl;
}


template <typename T>
void Graph<T>::print() {
    std::cout << "Vertices: " << std::endl;
    Node<Vertex<T>*>* currentNode = vertices.getHead();
    while (currentNode) {
        std::cout << currentNode->getData()->getData() << "==> [";
        Node<Vertex<T>*>* currentNodeEdge = currentNode->getData()->getEdges().getHead();
        while(currentNodeEdge) {
            cout << currentNodeEdge->getData()->getData() << ", ";
            currentNodeEdge = currentNodeEdge->getNext();
        }

        std::cout << "]" << std::endl;
        currentNode = currentNode->getNext();
    }
        
}

template <typename T>
unsigned int Graph<T>::size() const {
    return vertices.size();
}