#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
    private:
        T* data = nullptr;

        unsigned int capacity = 0;
        unsigned int size = 0;
    public:
        Vector();
        void reAllocate(unsigned int newCapacity);
        void pushBack(T value);
        const T& operator[](unsigned int index) const;
        T& operator[](unsigned int index);
        unsigned int length() const;

        void print() const;
};

#include "Vector.tpp"

#endif