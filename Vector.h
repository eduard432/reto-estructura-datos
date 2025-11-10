#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector {
    private:
        T* data = nullptr;

        unsigned int capacity = 0;
        unsigned int size = 0;
    public:
        Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
        ~Vector();
        void reAllocate(unsigned int newCapacity);
        void pushBack(T value);
        const T& operator[](unsigned int index) const;
        T& operator[](unsigned int index);
        unsigned int length() const;

        void print() const;
        int indexOf(const T& v) const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Vector<U>& v);
};

#include "Vector.tpp"

#endif