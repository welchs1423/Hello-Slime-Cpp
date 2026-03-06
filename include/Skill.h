#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill
{
public:
    std::string name;
    int mpCost;     // 소모 마나
    int baseDamage; // 기본 스킬 데미지
    int type;       // 1: 물리(근력 비례), 2: 마법(지능 비례), 3: 회복

    Skill(std::string n, int cost, int dmg, int t);
    std::string getTypeName();
};

#endif