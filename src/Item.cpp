#include "../include/Item.h"

Item::Item(std::string n, int t, int v, int p, bool e) 
    : name(n), type(t), effectValue(v), price(p), isEquipped(e) {}

std::string Item::getTypeName() {
    if (type == 1) return "무기";
    if (type == 2) return "방어구";
    if (type == 3 || type == 4) return "소모품";
    return "기타";
}