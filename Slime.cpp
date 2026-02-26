#include "Slime.h"
#include <cstdlib>

Slime::Slime(int playerLevel){
    maxHp = 30 + (playerLevel * 10);    // 플레이어 레벨에 비례헤 체력 증가
    hp = maxHp;
    baseDamage = 5 + playerLevel;   // 기본 데미지도 레벨에 비례해 증가
}

int Slime::attack(){
    return (rand() % 5) + baseDamage;   // 랜덤 데미지 계산 후 반환
}

void Slime::takeDamage(int damage) {
    hp -= damage;
}