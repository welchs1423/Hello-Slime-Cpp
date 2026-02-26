#include "../include/Goblin.h"

// 부모 클래스(Monster)의 생성자를 호출하여 이름, HP, 공격력을 설정합니다.
Goblin::Goblin(int playerLevel) 
    : Monster("Green Goblin", 50 + (playerLevel * 15), 10 + playerLevel) {
}