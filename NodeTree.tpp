#include "NodeTree.h"

template <typename T>
T NodeTree<T>::getData() {
    return data;
}

template <typename T>
NodeTree<T>* NodeTree<T>::getLeft() {
    return left;
}

template <typename T>
NodeTree<T>* NodeTree<T>::getRight() {
    return right;
}

template <typename T>
int NodeTree<T>::getHeight () const {
    return height;
}

template <typename T>
void NodeTree<T>::setData(const T& v) {
    data = v;
}

template <typename T>
void NodeTree<T>::setRight(NodeTree<T>* right) {
    this->right = right;
}

template <typename T>
void NodeTree<T>::setLeft(NodeTree<T>* left) {
    this->left = left;
}

template <typename T>
void NodeTree<T>::setHeight(const int height) {
    this->height = height;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const NodeTree<U>& n) {
    os << n.getData();
    return os;
}