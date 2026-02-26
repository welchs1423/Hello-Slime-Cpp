#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "Monster.h"

class MonsterFactory {
public:
    // 던전 층수와 플레이어 레벨에 맞는 최적의 몬스터를 찍어낸다
    static Monster* spawnMonster(int floor, int playerLevel);
};

#endif