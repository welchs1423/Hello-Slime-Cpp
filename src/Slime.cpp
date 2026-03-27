#include "../include/Slime.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

Slime::Slime(int playerLevel) : Monster("푸른 슬라임", 30 + (playerLevel * 10), 5 + playerLevel) {}

void Slime::takeAction(Player &player)
{
    int decision = rand() % 100;
    // 체력이 30% 이하라면 50% 확률로 점액 재생
    if (hp < maxHp * 0.3 && decision < 50)
    {
        int heal = 10 + (maxHp / 10);
        hp += heal;
        if (hp > maxHp)
            hp = maxHp;
        std::cout << GREEN << name << "이(가) 몸을 웅크리며 점액을 재생합니다! (HP +" << heal << ")" << RESET << std::endl;
        return;
    }
    // 기본 행동
    player.takeDamage(attack());
}