#include "../include/Orc.h"
#include <iostream>
#include <cstdlib>

Orc::Orc(int playerLevel) : Monster("오크 전사", 80 + (playerLevel * 15), 15 + (playerLevel * 3)) {}

int Orc::attack()
{
    int decision = rand() % 100;
    if (decision < 20)
    {
        std::cout << "오크 전사가 무자비하게 내려찍습니다!" << std::endl;
        return (rand() % 10 + atk) * 2; // baseDamage 대신 atk 사용
    }
    return rand() % 5 + atk;
}