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

    // 기본 행동: 그냥 공격 (자식 클래스에서 오버라이드 가능)
    virtual void takeAction(Player &player)
    {
        player.takeDamage(attack());
    }

    void takeDamage(int damage)
    {
        hp -= damage;
        if (hp < 0)
            hp = 0;
    }

    virtual int attack() { return atk; }
};

#endif