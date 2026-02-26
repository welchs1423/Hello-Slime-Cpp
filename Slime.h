#ifndef SLIME_H
#define SLIME_H
#include "Monster.h"

class Slime : public Monster{
public:
    Slime(int playerLevel) : Monster("Blue Slime", 30 + (playerLevel * 10), 5 + playerLevel) {}
};

#endif