#pragma once
#include "Vertex.h"
#include "LinkedList.h"

template <typename T>
void Vertex<T>::addEdge(Vertex<T>* u, int weight) {
    Edge<T> newEdge(u, weight);
    edges.pushBack(newEdge);
}

template <typename T>
T& Vertex<T>::getData() {
    return data;
}

template <typename T>
LinkedList<Edge<T>>& Vertex<T>::getEdges() {
    return edges;
}

template <typename T>
bool Vertex<T>::getVisited() const {
    return visited;
}

template <typename T>
void Vertex<T>::setVisited(const bool& v) {
    visited = v;
} 


template <typename T>
void Vertex<T>::setIndex(const unsigned int& i) {
    index = i;
}

template <typename T>
unsigned int Vertex<T>::getIndex() const {
    return index;
}

template <typename T>
bool Vertex<T>::operator==(const Vertex& other) const {
    return data == other.getData();
}