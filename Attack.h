#ifndef ATTACK_H
#define ATTACK_H

#include <string>
using namespace std;

class Attack {
    private:
        string name;
        float damage;
    public:
        Attack(const string& n, const float& d): name(n), damage(d) {}
        Attack() {
            name = "Ataque por defecto";
            damage = 1;
        }
        string getName() const;
        float getDamage() const;
        void setName(const string& n);
        void setDamage(const float& d);
};

#endif