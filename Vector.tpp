#pragma once
#include "Vector.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
Vector<T>::Vector() {
    reAllocate(2);
};

template <typename T>
void Vector<T>::reAllocate(unsigned int newCapacity) {
    T* newData = new T[newCapacity];

    if(newCapacity < size){
        size = newCapacity;
    }

    for (unsigned int i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
};

template <typename T>
void Vector<T>::pushBack(T value) {
    if(size >= capacity) {
        reAllocate(capacity + capacity / 2);
    }

    data[size] = value;
    size++;
};

template <typename T>
const T& Vector<T>::operator[](unsigned int index) const {
    if(size >= capacity) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
};

template <typename T>
T& Vector<T>::operator[](unsigned int index) {
    return data[index];
}

template <typename T>
unsigned int Vector<T>::length() const {
    return size;
}

template <typename T>
void Vector<T>::print() const {
    cout << "[";
    for (unsigned int i = 0; i < size; i++) {
        cout << data[i];
        if(i != size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}