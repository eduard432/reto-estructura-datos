#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <iostream>

using namespace std;

class Square {
    private:
        unsigned int id;
        string name;
        unsigned int probabilty;
        bool visited;

    public:
        Square(const unsigned int& i, const string& n, const unsigned int& p = 0, const bool& v = false): id(i), name(n), probabilty(p), visited(v) {};

        unsigned int getId() const;
        string getName() const;
        unsigned int getProbability() const;
        bool getVisited() const;
        bool operator==(const Square& other) const;
        friend ostream& operator<<(ostream& os, const Square& s);

        void setVisited(bool v);
};


#endif