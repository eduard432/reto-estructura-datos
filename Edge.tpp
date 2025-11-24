#pragma once
#include "Edge.h"

template <typename T>
Vertex<T>* Edge<T>::getVertex() const {
    return vertex;
}

template <typename T>
int Edge<T>::getWeight() const {
    return weight;
}