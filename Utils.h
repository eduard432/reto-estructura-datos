#ifndef UTILS_H
#define UTILS_H
#include <random>
#include "Vector.h"
#include <string>

using namespace std;

class Utils {
    public:
        static double randomDoubleNumber(const int& a = 0.0, const int& b = 1.0) {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dist(a, b);

            double num = dist(gen);
            return num;
        }
        static int randomIntNumber(const int& a = 0, const int& b = 10) {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dist(a, b);

            int num = dist(gen);
            return num;
        }
        static float max(const int& a, const int& b) {
            if(a >= b) return a;
            else return b;
        }
};


#endif