#ifndef GOBLIN_H
#define GOBLIN_H
#include "Monster.h"

class Goblin : public Monster {
public:
    Goblin(int playerLevel) : Monster("Green Goblin", 50 + (playerLevel * 15), 10 + playerLevel) {}
};

#endif