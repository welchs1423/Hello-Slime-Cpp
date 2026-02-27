#include "../include/MonsterFactory.h"
#include "../include/Slime.h"
#include "../include/Goblin.h"
#include "../include/KingSlime.h"
#include "../include/Orc.h"
#include <cstdlib>

Monster* MonsterFactory::spawnMonster(int floor, int playerLevel) {
    // 1. 보스 생성 로직 (5층 단위)
    if (floor % 5 == 0) {
        return new KingSlime(playerLevel); // 이제 평범한 몬스터가 아니라 진짜 보스 객체를 반환
    }

    // 2. 일반 몬스터 배정 로직 (Battle에서 이사 옴!)
    if (floor >= 7) {
        if (rand() % 2 == 0) return new Orc(playerLevel);
        return new Goblin(playerLevel);
    } 
    
    if (floor >= 3) {
        if (rand() % 2 == 0) return new Goblin(playerLevel);
        return new Slime(playerLevel);
    }

    return new Slime(playerLevel);
}