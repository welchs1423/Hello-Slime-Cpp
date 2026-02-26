#include "../include/Slime.h"

Slime::Slime(int playerLevel) 
    : Monster("Blue Slime", 30 + (playerLevel * 10), 5 + playerLevel) {}