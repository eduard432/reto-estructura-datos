#ifndef HERO_H
#define HERO_H

class Hero {
    private:
        float HP;
        float ATK;
        float DEF;
    public:
        Hero(const float& health = 100, const float& attack = 8, const float& defense = 5 ) {
            HP = health;
            ATK = attack;
            DEF = defense;
        }
        float getHP() const;
        float getATK() const;
        float getDEF() const;
        void setHP(const float& health);
        void setATK(const float& attack);
        void setDEF(const float& defense);

};

#endif