#include "../include/Orc.h"

// 슬라임(30+), 고블린(50+)보다 체력(100+)과 공격력을 부여
Orc::Orc(int playerLevel) 
    : Monster("Angry Orc", 100 + (playerLevel * 20), 20 + playerLevel) {
}