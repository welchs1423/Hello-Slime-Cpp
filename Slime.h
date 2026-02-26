#ifndef SLIME_H
#define SLIME_H

class Slime {
public:
    int hp;
    int maxHp;
    int baseDamage;

    Slime(int playerLevel); 
    int attack(); 
    void takeDamage(int damage); 
};

#endif