#ifndef NODE_TREE
#define NODE_TREE

#include <iostream>

template <typename T>
class NodeTree {
    private:
        T data;
        NodeTree<T>* left;
        NodeTree<T>* right;
        int height;
    public:
        explicit NodeTree(const T& v): data(v), left(nullptr), right(nullptr), height(1)  {}
        T getData();
        NodeTree<T>* getLeft();
        NodeTree<T>* getRight();
        int getHeight () const;
        void setData(const T& v);
        void setRight(NodeTree<T>* right);
        void setLeft(NodeTree<T>* left);
        void setHeight(const int height);

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const NodeTree<U>& n);
};

#include "NodeTree.tpp"

#endif