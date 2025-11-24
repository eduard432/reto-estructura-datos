#ifndef ATTACK_H
#define ATTACK_H

#include <string>
using namespace std;

class Attack {
    private:
        string name;
        float damage;
    public:
        Attack(const string& n = "Ataque por defecto", const float& d = 1.0): name(n), damage(d) {}
        string getName() const;
        float getDamage() const;
        void setName(const string& n);
        void setDamage(const float& d);
        friend ostream& operator<<(ostream& os, const Attack& a);
};

#endif