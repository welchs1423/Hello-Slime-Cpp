#include "../include/Item.h"

// 생성자
Item::Item(std::string n, int t, int v, int p)
    : name(n), type(t), effectValue(v), price(p) {}

// 타입 번호를 한글 문자열로 변환해주는 함수
std::string Item::getTypeName() {
    if (type == 1) return "무기";
    if (type == 2) return "방어구";
    if (type == 3) return "소모품";
    return "기타";
}