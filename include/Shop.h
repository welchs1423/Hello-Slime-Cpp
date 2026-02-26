#ifndef SHOP_H
#define SHOP_H
#include "Player.h"

class Shop{
public:
    // 원본 플레이어 데이터를 조작하기 위해 참조자(&) 사용
    void visit(Player& player);
};

#endif