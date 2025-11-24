#pragma once
#include <iostream>

#include "Vertex.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "Graph.h"
#include "PriorityQueue.h"

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
bool Graph<T>::addEdge(const T& v, const T& u, int weight) {
    
    int vIndex = indexOf(v);
    int uIndex = indexOf(u);
    
    if(vIndex == -1 || uIndex == -1) {
        return false;
    }

    vertices[vIndex]->addEdge(vertices[uIndex], weight);
    vertices[uIndex]->addEdge(vertices[vIndex], weight);

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

template <typename T>
LinkedList<int> Graph<T>::dijkstra(const T& start) {
    int startIndex = indexOf(start);
    if (startIndex == -1) {
        std::cout << "Nodo inicial no encontrado" << std::endl;
        return LinkedList<int>();
    }
    
    
    // Inicializar distancias
    LinkedList<int> distances;
    LinkedList<bool> visited;
    
    for (unsigned int i = 0; i < vertices.size(); i++) {
        distances.pushBack(INT_MAX);
        visited.pushBack(false);
    }
    
    distances[startIndex] = 0;
    
    // Priority Queue: menor distancia primero
    PriorityQueue<int> pq;
    pq.enqueue(startIndex, 0);
    
    while (!pq.isEmpty()) {
        int u = pq.dequeue();
        
        if (visited.elementAt(u)) continue;
        visited[u] = true;
        
        // Revisar todos los vecinos
        Node<Edge<T>>* edgeNode = vertices[u]->getEdges().getHead();
        while (edgeNode) {
            Edge<T> edge = edgeNode->getData();
            Vertex<T>* neighbor = edge.getVertex();
            int v = neighbor->getIndex();
            int weight = edge.getWeight();
            
            if (!visited.elementAt(v)) {
                int newDist = distances.elementAt(u) + weight;
                
                if (newDist < distances.elementAt(v)) {
                    distances[v] = newDist;
                    pq.enqueue(v, newDist);
                }
            }
            
            edgeNode = edgeNode->getNext();
        }
    }
    
    return distances;
}

template <typename T>
LinkedList<T> Graph<T>::dijkstraPath(const T& start, const T& end) {
    int startIndex = indexOf(start);
    int endIndex = indexOf(end);
    
    if (startIndex == -1 || endIndex == -1) {
        std::cout << "Nodo inicial o final no encontrado" << std::endl;
        return LinkedList<T>();
    }
    
    LinkedList<int> distances;
    LinkedList<bool> visited;
    LinkedList<int> previous;
    
    for (unsigned int i = 0; i < vertices.size(); i++) {
        distances.pushBack(INT_MAX);
        visited.pushBack(false);
        previous.pushBack(-1);
    }
    
    distances[startIndex] = 0;
    PriorityQueue<int> pq;
    pq.enqueue(startIndex, 0);
    
    while (!pq.isEmpty()) {
        int u = pq.dequeue();
        
        if (u == endIndex) break;
        if (visited.elementAt(u)) continue;
        
        visited[u] = true;
        
        Node<Edge<T>>* edgeNode = vertices[u]->getEdges().getHead();
        while (edgeNode) {
            Edge<T> edge = edgeNode->getData();
            Vertex<T>* neighbor = edge.getVertex();
            int v = neighbor->getIndex();
            int weight = edge.getWeight();
            
            if (!visited.elementAt(v)) {
                int newDist = distances.elementAt(u) + weight;
                
                if (newDist < distances.elementAt(v)) {
                    distances[v] = newDist;
                    previous[v] = u;
                    pq.enqueue(v, newDist);
                }
            }
            
            edgeNode = edgeNode->getNext();
        }
    }
    
    // Reconstruir camino
    LinkedList<T> path;
    
    if (distances.elementAt(endIndex) == INT_MAX) {
        std::cout << "No hay camino entre los nodos" << std::endl;
        return path;
    }
    
    Stack<int> reversePath;
    int curr = endIndex;
    
    while (curr != -1) {
        reversePath.push(curr);
        curr = previous.elementAt(curr);
    }
    
    while (!reversePath.isEmpty()) {
        int idx = reversePath.pop();
        path.pushBack(vertices[idx]->getData());
    }
    
    return path;
}

template <typename T>
void Graph<T>::dijkstraPrint(const T& start) {
    LinkedList<int> distances = dijkstra(start);
    
    if (distances.isEmpty()) return;
    
    std::cout << "Distancias mínimas desde " << start << ":" << std::endl;
    std::cout << "================================" << std::endl;
    
    for (unsigned int i = 0; i < vertices.size(); i++) {
        std::cout << "Nodo " << vertices[i]->getData() << ": ";
        
        int dist = distances.elementAt(i);
        if (dist == INT_MAX) {
            std::cout << "INT_MAX (no alcanzable)" << std::endl;
        } else {
            std::cout << dist << std::endl;
        }
    }
}