#pragma once
#include "Graph.h"
#include <iostream>

using namespace std;

template <typename T>
int Graph<T>::indexOf(const T& v) const {
    return vertices.indexOf(v);
}

template <typename T>
bool Graph<T>::addVertex(const T& v) {
    if(indexOf(v) != - 1) {
        return false;
    }
    
    vertices.pushBack(v);
    
    for (unsigned int i = 0; i < matrix.length(); i++) {
        matrix[i].pushBack(0);
    }
    
    Vector<int> newVector;
    for (unsigned int i = 0; i < vertices.length(); i++) {
        newVector.pushBack(0);
    }
    
    matrix.pushBack(newVector);
    
    return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& v, const T& u, int weight, bool directed) {
    int iu = indexOf(u);
    int iv = indexOf(v);

    if(iu == -1 || iv == -1) return false;

    matrix[iu][iv] = weight;
    if(directed) {
        matrix[iv][iu] = weight;
    }

    return true;
}

template <typename T>
void Graph<T>::printMatrix() const {
    cout << "Adjacency matrix" << endl;
    for(unsigned int i = 0; i < matrix.length(); i++) {
        for (unsigned int j = 0; j < matrix[i].length(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}