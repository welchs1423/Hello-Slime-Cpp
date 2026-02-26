#include "Monster.h"
#include "Colors.h"
#include <iostream>

using namespace std;

Monster::Monster(string n, int h, int d) : name(n), maxHp(h), hp(h), baseDamage(d) {}

int Monster::attack(){
    int damage = rand() % 10 + baseDamage;
    return damage;
}

void Monster::takeDamage(int damage){
    hp -= damage;
    cout << name << " took " << damage << " damage. " << endl;
}