#ifndef SQUARE_H
#define SQUARE_H

#include <string>

using namespace std;

class Square {
    private:
        unsigned int id;
        string name;
        float probabilty;
        bool visited;

    public:
        Square(const unsigned int& i, const string& n, const float& p = 0.0, const bool& v = false): id(i), name(n), probabilty(p), visited(v) {};

        unsigned int getId() const;
        string getName() const;
        float getProbability() const;
        bool getVisited() const;
        bool operator==(const Square& other) const;
};

#include "Square.tpp"

#endif