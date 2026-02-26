#include "Slime.h"
#include <cstdlib>

Slime::Slime(int playerLevel) {
    maxHp = 30 + (playerLevel * 10); 
    hp = maxHp;
    baseDamage = 5 + playerLevel;    
}

int Slime::attack() {
    return (rand() % 5) + baseDamage; 
}

void Slime::takeDamage(int damage) {
    hp -= damage;
}