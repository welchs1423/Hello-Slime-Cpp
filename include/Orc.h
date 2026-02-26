#ifndef ORC_H
#define ORC_H

#include "Monster.h"

class Orc : public Monster {
public:
    // 고블린보다 높은 체력과 데미지를 설정
    Orc(int playerLevel);
};

#endif