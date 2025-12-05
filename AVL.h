#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "NodeTree.h"

template <typename T>
class AVL {
    private:
        NodeTree<T>* root;

        // utils
        int height(NodeTree<T>* n) const;
        int balanceFactor(NodeTree<T>* n ) const;
        int maxValue(const int a, const int b) const;

        // Rotations
        NodeTree<T>* rotateRight(NodeTree<T>* node);
        NodeTree<T>* rotateLeft(NodeTree<T>* node);
        NodeTree<T>* rotateLeftRight(NodeTree<T>* node);
        NodeTree<T>* rotateRightLeft(NodeTree<T>* node);

        NodeTree<T>* insert(NodeTree<T>* node, const T& value);
        NodeTree<T>* remove(NodeTree<T>* node, const T& value);
        void print(NodeTree<T>* node) const;
        bool ancestors(const T& value, NodeTree<T>* node) const;

        NodeTree<T>* search(NodeTree<T>* root, const T& val) const;
        
    public:
        AVL(): root(nullptr){}
        ~AVL();
        void print() const;
        void clear();

        int getHeight() const;

        void remove(const T& value);
        void insert(const T& value);
        void ancestors(const T& value) const;

        NodeTree<T>* search( const T& val) const;
        
};

#include "AVL.tpp"

#endif