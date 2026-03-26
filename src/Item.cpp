#include "../include/Item.h"

// 생성자 정의
Item::Item(std::string n, int t, int e, int p, bool eq)
    : name(n), type(t), effectValue(e), price(p), isEquipped(eq), socketGem(0) {}

// 타입 이름 반환 함수 정의
std::string Item::getTypeName() const
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