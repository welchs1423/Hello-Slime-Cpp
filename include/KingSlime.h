#ifndef KINGSLIME_H
#define KINGSLIME_H

#include "Monster.h"

class KingSlime : public Monster {
public:
    KingSlime(int playerLevel);
    int attack() override;  // 보스만의 특수 패턴
};

#endif