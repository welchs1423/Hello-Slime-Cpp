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
    int socketGem; // 0: 없음, 1: 루비(공격력), 2: 사파이어(마나)

    Item(std::string n, int t, int e, int p, bool eq = false)
        : name(n), type(t), effectValue(e), price(p), isEquipped(eq), socketGem(0) {}

    std::string getTypeName() const
    {
        if (type == 1)
            return "무기";
        if (type == 2)
            return "방어구";
        if (type == 3)
            return "포션(HP)";
        if (type == 4)
            return "포션(MP)";
        if (type == 5)
            return "만병통치약";
        if (type == 6)
            return "보석";
        return "기타";
    }
};

#endif