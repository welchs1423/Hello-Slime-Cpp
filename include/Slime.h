#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"

class Slime : public Monster
{
public:
    Slime(int playerLevel);
    void takeAction(Player &player) override; // AI 로직 선언
};

#endif