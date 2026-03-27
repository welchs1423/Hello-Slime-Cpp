#include "../include/Goblin.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

Goblin::Goblin(int playerLevel) : Monster("초록 고블린", 50 + (playerLevel * 12), 8 + (playerLevel * 2)) {}

void Goblin::takeAction(Player &player)
{
    int decision = rand() % 100;
    // 플레이어 빈사 시 결정타
    if (player.hp < player.maxHp * 0.2)
    {
        std::cout << RED << name << "이(가) 비열하게 웃으며 급소를 노립니다!" << RESET << std::endl;
        player.takeDamage(attack() * 2);
    }
    // 플레이어 마나 연소
    else if (player.mp >= 50 && decision < 30)
    {
        int burn = 15;
        player.mp -= burn;
        if (player.mp < 0)
            player.mp = 0;
        std::cout << MAGENTA << name << "이(가) 마나를 태우는 독연기를 뿜습니다! (MP -" << burn << ")" << RESET << std::endl;
        player.takeDamage(attack() / 2);
    }
    else
    {
        player.takeDamage(attack());
    }
}