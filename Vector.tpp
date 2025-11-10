#pragma once
#include "Vector.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
Vector<T>::Vector() {
    data = nullptr;
    capacity = 0;
    size = 0;
    reAllocate(2);
};

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
};

template <typename T>
Vector<T>::Vector(const Vector& other) {
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for(unsigned int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
};

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if(this == &other) return *this;
    delete[] data;
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for(unsigned int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    return *this;
};

template <typename T>
int Vector<T>::indexOf(const T& v) const {
    for (unsigned int i = 0; i < size; i++) {
        if(v == data[i]) {
            return i;
        }
    }

    return -1;
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
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
};

template <typename T>
T& Vector<T>::operator[](unsigned int index) {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
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

template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& v) {
    v.print();
    return os;
}