#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    std::string name;
    int type;           // 1: 무기,  2: 방어구, 3: 소모품
    int effectValue;    // 올려주는 수치 (공격력, 방어력, 회복량 등)
    int price;          // 상점 가격

    Item(std::string n, int t, int v, int p);
    std::string getTypeName();  // "무기", "방어구" 같은 글자를 반환
};

#endif