#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
    std::string name;
    int type; // 1: 무기, 2: 방어구, 3: 체력포션, 4: 마나포션, 5: 만병통치약, 6: 보석
    int effectValue;
    int price;
    bool isEquipped;
    int socketGem; // 0: 없음, 1: 루비, 2: 사파이어

    // 생성자 선언
    Item(std::string n, int t, int e, int p, bool eq = false);

    // 타입 이름 반환 함수 선언
    std::string getTypeName() const;
};

#endif