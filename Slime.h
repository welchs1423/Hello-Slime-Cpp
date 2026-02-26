#ifndef SLIME_H
#define SLIME_H

class Slime {
public:
    int hp;
    int maxHp;
    int baseDamage;

    // 생성자: 플레이어의 레벨을 받아서 그에 맞게 강해진 슬라임을 생성합니다,
    Slime(int playerLevel);

    int attack();   // 슬라임의 공격
    void takeDamage(int damage);    // 슬라임이 피해를 입음
};

#endif