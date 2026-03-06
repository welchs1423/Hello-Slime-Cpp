#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include "Item.h"
#include "Skill.h" // ✨ 스킬 설계도 추가

class Job;

class Player
{
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

    int str;
    int intel;
    int vit;
    int statPoints;

    int jobClass;
    Job *job;

    std::vector<Item> inventory;
    std::vector<Skill> skills;

    int activeQuestId;
    int questProgress;

    std::map<std::string, int *> stats;

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