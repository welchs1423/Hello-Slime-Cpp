#include "../include/Orc.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// 슬라임(30+), 고블린(50+)보다 체력(100+)과 공격력을 부여
Orc::Orc(int playerLevel) : Monster("Angry Orc", 100 + (playerLevel * 20), 20 + playerLevel) {}

int Orc::attack(){
    int chance = rand() % 100;
    if(chance < 20){    // 20% 확률로 2배 데미지 강타
        int damage = (rand() % 10 + baseDamage) * 2;
        cout << RED << name << " swings its massive club! [HEAVY SMASH] dealt " << damage << " damage!" << RESET << endl;
        return damage;
    }
    // 스킬이 안 터지면 부모(Monster)의 기본 공격 사용
    return Monster::attack();
}