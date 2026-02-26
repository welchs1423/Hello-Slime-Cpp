#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster{
public:
    std::string name;
    int hp;
    int maxHp;
    int baseDamage;

    Monster(std::string n, int h, int d);
    virtual ~Monster() {}   // 상속용 가상 소멸자

    virtual int attack();   // 몬스터마다 공격 방식이 다를 수 있음
    virtual void takeDamage(int damage);
};

#endif