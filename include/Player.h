#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include "Item.h"

class Job;

class Player {
public:
    std::string name;
    int level;
    int maxHp; int hp;
    int maxMp; int mp;
    int weaponDamage;
    int armorDefense;
    int exp; int maxExp;
    int gold;
    int potions; int manaPotions;
    int dungeonFloor;
    int weaponLevel; int armorLevel;
    
    int str;        // 근력 (물리 공격력)
    int intel;      // 지능 (마법 공격력 및 마나)
    int vit;        // 체력 (최대 체력)
    int statPoints; // 잔여 스탯 포인트
    
    int jobClass;   
    Job* job;       

    std::vector<Item> inventory; 
    int activeQuestId;  
    int questProgress;  

    std::map<std::string, int*> stats;

    Player();
    ~Player();

    void registerStats();
    void updateJobLogic(); 
    void chooseClass();    
    void openInventory();  
    void allocateStats();
    void printStatus();
    int attack();
    int magicAttack();
    void takeDamage(int damage);
    void heal();
    void restoreMp();
    void gainExp(int amount);
    void levelUp();        

    void save();
    void load();
};

#endif