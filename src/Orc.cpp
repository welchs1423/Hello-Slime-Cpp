#include "../include/Orc.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Orc::Orc(int playerLevel) : Monster("성난 오크", 100 + (playerLevel * 20), 20 + playerLevel) {}

int Orc::attack(){
    int chance = rand() % 100;
    if(chance < 20){ 
        int damage = (rand() % 10 + baseDamage) * 2;
        cout << RED << name << "이(가) 거대한 몽둥이를 휘두릅니다! [강타] " << damage << " 피해!" << RESET << endl;
        return damage;
    }
    return Monster::attack();
}