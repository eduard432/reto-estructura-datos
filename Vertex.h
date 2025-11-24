#ifndef VERTEX_H
#define VERTEX_H

#include "LinkedList.h"
#include "Edge.h"

template <typename T>
class Vertex {
    private:
        LinkedList<Edge<T>> edges;
        T data;
        bool visited;
        unsigned int index;
    public:
        Vertex(const T& v): data(v) {};
        void addEdge(Vertex<T>* u, int weight = 1);
        T& getData();
        bool getVisited() const;
        void setVisited(const bool& v);

        unsigned int getIndex() const;
        void setIndex(const unsigned int& i);
        bool operator==(const Vertex& other) const;

        template <typename U>
        friend ostream& operator<<(ostream& os, const Vertex<U>& s);

        LinkedList<Edge<T>>& getEdges();

};

#include "Vertex.tpp"


#endif