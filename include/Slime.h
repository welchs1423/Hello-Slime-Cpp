#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"

class Slime : public Monster {
public:
    Slime(int playerLevel);
    int attack() override; // 슬라임만의 공격 방식 선언
};

#endif