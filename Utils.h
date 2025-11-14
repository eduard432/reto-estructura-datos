#ifndef UTILS_H
#define UTILS_H
#include <random>

using namespace std;

class Utils {
    public:
        static double randomNumber() {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dist(0.0, 1.0);

            double num = dist(gen);
            return num;
        }

};


#endif