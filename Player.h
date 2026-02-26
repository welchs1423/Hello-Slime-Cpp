#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>

class Player {
private:
    // 변수 이름과 해당 주소를 연결하는 맵
    std::map<std::string, int*> stats;
    void registerStats();   // 스탯 등록 함수
    
public:
    int level;
    int exp;
    int maxHp;
    int maxMp;  // Added Max Mp
    int mp;     // Added Current Mp
    int hp;
    int potions;
    int manaPotions;    // 추가 : 마나포션
    int gold;   // Added Gold
    int weaponDamage;   // Added Weapon Damage
    int armorDefense;   // Added Armor Defense
    int dungeonFloor;   // Added Dungeon Floor

    Player(); 
    int attack(); 
    int magicAttack();  // Added Magic Attack Skill
    void takeDamage(int damage); 
    void heal(); 
    void restoreMp();   // 추가 : 마나 회복 함수
    void gainExp(int amount); 
    void printStatus(); 

    // File I/O for Save & Load
    void save();
    bool load();
};

#endif