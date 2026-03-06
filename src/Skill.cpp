#include "../include/Skill.h"

Skill::Skill(std::string n, int cost, int dmg, int t)
    : name(n), mpCost(cost), baseDamage(dmg), type(t) {}

std::string Skill::getTypeName()
{
    if (type == 1)
        return "물리";
    if (type == 2)
        return "마법";
    if (type == 3)
        return "회복";
    return "기타";
}