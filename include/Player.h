#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Item.h"
#include "Skill.h"

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

    int weaponDurability;
    int armorDurability;
    int totalKills;
    bool achMonsterHunter;
    bool achRichMan;
    int innkeeperAffinity;
    int rebirthCount;

    int jobClass;
    std::unique_ptr<Job> job;

    std::vector<Item> inventory;
    std::vector<Skill> skills;

    int activeQuestId;
    int questProgress;

    std::map<std::string, int *> stats;

    Player();
    ~Player();

    void registerStats();
    void chooseClass();
    void openInventory();
    void allocateStats();
    void resetStats();
    void checkAchievements();
    void doRebirth();

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