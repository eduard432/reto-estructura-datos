#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"

template <typename T>
class Graph {
    private:
        int n;
        int count;
        Vector<Vector<int>> matrix;
        Vector<T> vertices;
        int indexOf(const T& v) const;
        
    public:
        Graph() {
            Vector<int> vector;
        };
        bool addVertex(const T& val);
        bool addEdge(const T& v, const T& u, int weight = 1, bool directed = false);

        void printMatrix() const;
        
};

#include "Graph.tpp"

#endif