#include "../include/KingSlime.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// 스탯은 기존 MonsterFactory에 있던 보스 스탯 그대로 가져옴
KingSlime::KingSlime(int playerLevel) : Monster("KING SLIME", 300 + (playerLevel * 30), 25 + playerLevel) {}

int KingSlime::attack(){
    int chance = rand() % 100;

    if(chance < 25){
        // 25% 확률:대지진 (2배 데미지)
        int damage = baseDamage * 2;
        cout << RED << "[보스 패턴] 킹 슬라임이 거대한 몸집으로 짓누릅니다! (대지진) " << damage << " 피해!" << RESET << endl;
        return damage;
    } else if(chance < 40){
        // 15% 확률 자체 회복 (공격 X)
        hp += 50;
        if (hp > maxHp) hp = maxHp;
        cout << GREEN << "[보스 패턴] 킹 슬라임이 분열된 조각을 흡수하여 체력을 50 회복합니다!" << RESET << endl;
        return 0;   // 이번 턴은 데미지 0
    }

    return Monster::attack();
}