#include "../include/Slime.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Slime::Slime(int playerLevel) : Monster("Blue Slime", 30 + (playerLevel * 10), 5 + playerLevel) {}

int Slime::attack(){
    int chance = rand() % 100;
    if(chance < 30){     // 30% 확률로 방어력을 무시하는 느낌의 산성 공격
        int damage = baseDamage + 15; // 고정 추가 데미지
        cout << GREEN << name << " spits corrosive acid! [ACID SPIT] dealt " << damage << " damage!" << RESET << endl;
        return damage;
    }
    return Monster::attack();
}