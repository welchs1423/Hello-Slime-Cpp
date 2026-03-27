#include "../include/KingSlime.h"
#include <iostream>
#include <cstdlib>

KingSlime::KingSlime(int playerLevel) : Monster("거대 킹 슬라임", 200 + (playerLevel * 20), 20 + (playerLevel * 4)) {}

int KingSlime::attack()
{
    int decision = rand() % 100;
    if (decision < 30)
    {
        std::cout << "거대 킹 슬라임이 거대한 몸집으로 짓누릅니다!" << std::endl;
        return atk * 2; // baseDamage 대신 atk 사용
    }
    return rand() % 10 + atk;
}