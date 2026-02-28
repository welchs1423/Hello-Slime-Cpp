#include "../include/Slime.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Slime::Slime(int playerLevel) : Monster("푸른 슬라임", 30 + (playerLevel * 10), 5 + playerLevel) {}

int Slime::attack(){
    int chance = rand() % 100;
    if(chance < 30){
        int damage = baseDamage + 15;
        cout << GREEN << name << "이(가) 부식성 산성액을 뱉습니다! [산성액] " << damage << " 피해!" << RESET << endl;
        return damage;
    }
    return Monster::attack();
}