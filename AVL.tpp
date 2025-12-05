#pragma once
#include "AVL.h"
#include <iostream>

using namespace std;
template <typename T>
void AVL<T>::print(NodeTree<T>* node) const {
    if (node == nullptr)
        return;

    cout << "Nodo: " << node->getData() << " (Izq: ";
    if (node->getLeft())
        cout << node->getLeft()->getData();
    else
        cout << "null";

    cout << ", Der: ";
    if (node->getRight())
        cout << node->getRight()->getData();
    else
        cout << "null";
    cout << ")" << endl;
    print(node->getLeft());
    print(node->getRight());
}
/* util */
template <typename T>
int AVL<T>::height(NodeTree<T>* n) const {
    return n ? n->getHeight():0;
}
template <typename T>
int AVL<T>::balanceFactor(NodeTree<T>* n) const {
    if (!n) {
        return 0;
    }
    return height(n->getLeft()) - height(n->getRight());
}
template <typename T>
int AVL<T>::maxValue(int a, int b) const {
    return (a>b) ? a : b;
}

/* rotations */
template <typename T>
NodeTree<T>* AVL<T>::rotateRight(NodeTree<T>* node) {
    NodeTree<T>* temp= node->getLeft();
    NodeTree<T>* temp2= temp->getRight();
    temp->setRight(node);
    node->setLeft(temp2);
    node->setHeight(1+ maxValue(height(node->getLeft()), height(node->getRight())));
    temp->setHeight(1+ maxValue(height(temp->getRight()), height(temp->getLeft())));
    return temp;
}
template <typename T>
NodeTree<T>* AVL<T>::rotateLeft(NodeTree<T>* node) {
    NodeTree<T>* temp= node->getRight();
    NodeTree<T>* temp2= temp->getLeft();
    temp->setLeft(node);
    node->setRight(temp2);
    node->setHeight(1+ maxValue(height(node->getLeft()), height(node->getRight())));
    temp->setHeight(1+ maxValue(height(temp->getRight()), height(temp->getLeft())));
    return temp;
}
template <typename T>
NodeTree<T>* AVL<T>::rotateLeftRight(NodeTree<T>* node) {
    node->setLeft( rotateLeft(node->getLeft()));
    return rotateRight(node);
}

template <typename T>
NodeTree<T>* AVL<T>::rotateRightLeft(NodeTree<T>* node) {
    node->setRight( rotateRight(node->getRight()));
    return rotateLeft(node);
}
template <typename T>
NodeTree<T>* AVL<T>::insert(NodeTree<T>* node, const T& value) {
    if (!node) {
        return new NodeTree<T>(value);
    }
    if (value < node->getData()) {
        node->setLeft(insert(node->getLeft(),value));
    }else if (value > node->getData()) {
        node->setRight(insert(node->getRight(), value));
    }else {
        return node;
    }

    node->setHeight(1 + maxValue(height(node->getLeft()),height(node->getRight())));
    const int bf = balanceFactor(node);
    if (bf > 1 && value < node->getLeft()->getData()) {
        return rotateRight(node);
    }
    if (bf< - 1 && value > node->getRight()->getData()) {
        return rotateLeft(node);
    }
    if (bf > 1 && value > node->getLeft()->getData()) {
        return rotateLeftRight(node);
    }
    if (bf< -1 && value < node->getRight()->getData()) {
        return rotateRightLeft(node);
    }
    return node;
}

template <typename T>
void AVL<T>::remove(const T& value) {
    remove(root, value);
}

template <typename T>
NodeTree<T>* AVL<T>::remove(NodeTree<T>* node, const T& value) {
    if(node == nullptr) {
        return nullptr;
    }
    
    if(value < node->getData()) {
        node->setLeft(remove(node->getLeft(), value));
    } else if(value > node->getData()) {
        node->setRight(remove(node->getRight(), value));
    } else {
        // Nodo encontrado
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            delete node;
            return nullptr;
        } else if (node->getLeft() == nullptr) {
            NodeTree<T>* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr) {
            NodeTree<T>* temp = node->getLeft();
            delete node;
            return temp;
        } else {
            // Dos hijos: usar predecesor inorden
            NodeTree<T>* maxNode = node->getLeft();
            while (maxNode->getRight() != nullptr) {
                maxNode = maxNode->getRight();
            }
            node->setData(maxNode->getData());
            node->setLeft(remove(node->getLeft(), maxNode->getData()));
        }
    }
    
    node->setHeight(1 + maxValue(height(node->getLeft()), height(node->getRight())));
    
    const int bf = balanceFactor(node);
    
    if (bf > 1 && balanceFactor(node->getLeft()) >= 0) {
        return rotateRight(node);
    }
    if (bf < -1 && balanceFactor(node->getRight()) <= 0) {
        return rotateLeft(node);
    }
    if (bf > 1 && balanceFactor(node->getLeft()) < 0) {
        return rotateLeftRight(node);
    }
    if (bf < -1 && balanceFactor(node->getRight()) > 0) {
        return rotateRightLeft(node);
    }
    
    return node;
}


template <typename T>
void AVL<T>::ancestors(const T& value) const { 
    ancestors(value, root);
}


template <typename T>
bool AVL<T>::ancestors(const T& value, NodeTree<T>* node) const {
    if(node == nullptr) {
        cout << "notFound" << endl;
        return false;
    }
    
    cout << node->getData() << "->";
    
    if(value == node->getData()) {
        cout << "Found" << endl;
        return true;
    }
    
    if(value < node->getData()) {
        return ancestors(value, node->getLeft());
    } else {
        return ancestors(value, node->getRight());
    }
}

template <typename T>
AVL<T>::~AVL() {

}
template <typename T>
void AVL<T>::clear() {

}
template <typename T>
void AVL<T>::print() const {
    print(root);
}
template <typename T>
void AVL<T>::insert(const T& value) {
    root= insert(root, value);
}

template <typename T>
int AVL<T>::getHeight() const {
    return height;
}

template <typename T>
NodeTree<T>* AVL<T>::search( const T& val) const {
    return search(root, val);
}

// Método recursivo para encontrar un nodo
// Complejidad: O(n)
template <typename T>
NodeTree<T>* AVL<T>::search(NodeTree<T>* root, const T& val) const {
    // Casos base:

    // El nodo no se encontro
    if(root == nullptr) {
        return nullptr;
    }
    // Se encontro el nodo
    if(val == root->getData()) {
        return root;
    }

    // Recursión
    // Biscamos derecha o izquierda dependiendo si es más chico o más grande
    // el valor dado
    if(val < root->getData()) {
        return search(root->getLeft(), val);
    } else {
        return search(root->getRight(), val);
    }
}