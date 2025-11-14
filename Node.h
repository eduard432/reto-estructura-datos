#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    private:
        T data;
        Node<T>* prev;
        Node<T>* next;

    public:
        Node(const T& val): data(val), prev(nullptr), next(nullptr) {};

        T getData() const;
        T& getDataRef();
        Node<T>* getPrev() const;
        Node<T>* getNext() const;

        void setData(const T& val);
        void setPrev(Node<T>* node);
        void setNext(Node<T>* node);
};

#include "Node.tpp"

#endif