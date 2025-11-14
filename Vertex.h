#ifndef VERTEX_H
#define VERTEX_H

#include "LinkedList.h"

template <typename T>
class Vertex {
    private:
        LinkedList<Vertex<T>*> edges;
        T data;
        bool visited;
        unsigned int index;
    public:
        Vertex(const T& v): data(v) {};
        void addEdge(Vertex<T>* u);
        T getData() const;
        bool getVisited() const;
        void setVisited(const bool& v);

        unsigned int getIndex() const;
        void setIndex(const unsigned int& i);

        LinkedList<Vertex<T>*>& getEdges();

};

#include "Vertex.tpp"


#endif