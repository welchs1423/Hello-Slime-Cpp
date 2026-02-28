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
    cout << name << "에게 " << damage << "의 데미지! " << endl;
}