#include "../include/Goblin.h"

Goblin::Goblin(int playerLevel) 
    : Monster("초록 고블린", 50 + (playerLevel * 15), 10 + playerLevel) {}