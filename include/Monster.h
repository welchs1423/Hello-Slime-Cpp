#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Player.h"

class Monster
{
public:
    std::string name;
    int hp;
    int maxHp;
    int atk;

    Monster(std::string n, int h, int a) : name(n), hp(h), maxHp(h), atk(a) {}
    virtual ~Monster() {}

    // 몬스터의 사고 모델: 상황에 따라 다른 행동을 취함
    virtual void takeAction(Player &player) = 0;

    void takeDamage(int damage)
    {
        hp -= damage;
        if (hp < 0)
            hp = 0;
    }

    virtual int attack() { return atk; }
};

// 각 몬스터별 특화 AI 구현을 위한 서브클래스
class Slime : public Monster
{
public:
    Slime(int floor, int playerLevel);
    void takeAction(Player &player) override;
};

class Goblin : public Monster
{
public:
    Goblin(int floor, int playerLevel);
    void takeAction(Player &player) override;
};

#endif