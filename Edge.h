#ifndef EDGE_H
#define EDGE_H

template <typename T> class Vertex;

template <typename T>
class Edge {
    private:
        Vertex<T>* vertex;
        int weight;
    public:
        Edge(Vertex<T>* v = nullptr, int w = 1): vertex(v), weight(w){}

        Vertex<T>* getVertex() const;
        int getWeight() const;
};

#include "Edge.tpp"

#endif