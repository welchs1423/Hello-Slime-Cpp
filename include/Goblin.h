#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"

class Goblin : public Monster
{
public:
    Goblin(int playerLevel);
    void takeAction(Player &player) override; // AI 로직 선언
};

#endif