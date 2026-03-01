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
    int maxHp;
    int hp;
    int maxMp;
    int mp;
    int weaponDamage;
    int armorDefense;
    int exp;
    int maxExp;
    int gold;
    int potions;
    int manaPotions;
    int dungeonFloor;
    int weaponLevel;
    int armorLevel;
    
    int jobClass;   
    Job* job;       

    std::vector<Item> inventory; 

    int activeQuestId;  // 0이면 진행 중인 퀘스트 없음
    int questProgress;  // 현재 사냥한 몬스터 마리 수 등

    std::map<std::string, int*> stats;

    Player();
    ~Player();

    void registerStats();
    void updateJobLogic(); 
    void chooseClass();    
    void openInventory();  
    
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