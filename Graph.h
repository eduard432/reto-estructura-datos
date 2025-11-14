#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "Vertex.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"


template <typename T>
class Graph {
    private:
        LinkedList<Vertex<T>*> vertices;
        void resetVisited();
    public:
        Graph() {}

        int indexOf(const T& data);
        Vertex<T>* vertexAt(const unsigned int i) const;

        bool addVertex(const T& data);

        bool addEdge(const T& v, const T& u);

        LinkedList<Vertex<T>*>& getVertices();

        void BFS(const T& start);

        void DFS(const T& start);

        void print();

        unsigned int size() const;
 
        ~Graph() {
            for (unsigned int i = 0; i < vertices.size(); i++) {
                delete vertices[i];
            }
        }
};

#include "Graph.tpp"

#endif