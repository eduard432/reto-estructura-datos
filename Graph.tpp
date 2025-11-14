#pragma once
#include <iostream>

#include "Vertex.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "Graph.h"

template <typename T>
void Graph<T>::resetVisited() {
    for(unsigned int i = 0; i < vertices.size(); i++) {
        vertices[i]->setVisited(false);
    }
}

template <typename T>
int Graph<T>::indexOf(const T& data) {
    for(unsigned int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->getData() == data) {
            return i;
        }
    }

    return -1;
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
    if(startIndex == -1) {
        std::cout << "Initial node not found" << std::endl;
        return;
    }
    resetVisited();
    Queue<int> queue;
    vertices[startIndex]->setVisited(true);
    queue.enqueue(startIndex);
    while(!queue.isEmpty()) {
        int index = queue.dequeue();
        std::cout << vertices[index]->getData() << "->";
        for (unsigned int i = 0; i < vertices[index]->getEdges().size(); i++) {
            if(!vertices[index]->getEdges()[i]->getVisited()) {
                vertices[index]->getEdges()[i]->setVisited(true);
                queue.enqueue(vertices[index]->getEdges()[i]->getIndex());
            }
        }
        

    }

    std::cout << std::endl;
}

template <typename T>
void Graph<T>::DFS(const T& start) {
    int startIndex = indexOf(start);
    if(startIndex == -1) {
        std::cout << "Initial node not found" << std::endl;
        return;
    }
    resetVisited();
    Stack<int> stack;
    vertices[startIndex]->setVisited(true);
    stack.push(startIndex);
    while(!stack.isEmpty()) {
        int index = stack.pop();
        std::cout << vertices[index]->getData() << "->";
        for (unsigned int i = 0; i < vertices[index]->getEdges().size(); i++) {
            if(!vertices[index]->getEdges()[i]->getVisited()) {
                vertices[index]->getEdges()[i]->setVisited(true);
                stack.push(vertices[index]->getEdges()[i]->getIndex());
            }
        }
        

    }

    std::cout << std::endl;
}

template <typename T>
void Graph<T>::print() {
    std::cout << "Vertices: " << std::endl;
    for (unsigned int i = 0; i < vertices.size(); i++){
        std::cout << vertices[i]->getData() << "==> [";
        for (unsigned int j = 0; j < vertices[i]->getEdges().size(); j++){
            std::cout << vertices[i]->getEdges()[j]->getData() << ", ";
        }
        std::cout << "]" << endl;
        
    }   
}