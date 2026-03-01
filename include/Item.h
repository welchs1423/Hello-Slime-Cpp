#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    std::string name;
    int type;        
    int effectValue; 
    int price;       
    bool isEquipped;

    // ✨ 끝에 bool e = false 를 주면, 기존 상점 코드를 하나도 안 고쳐도 기본으로 '장착 안 됨' 상태로 가방에 들어갑니다!
    Item(std::string n, int t, int v, int p, bool e = false);
    std::string getTypeName(); 
};

#endif