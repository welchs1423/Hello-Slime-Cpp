#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int level;
    int exp;
    int maxHp;
    int hp;
    int potions;

    Player();   // 기본 세팅을 해주는 생성자
    int attack();   // 공격하고 데미지를 반환하는 함수
    void takeDamage(int damage);    // 피해를 입는 함수
    void heal();    // 물약 먹는 함수
    void gainExp(int amount);   // 경험치 얻고 레벨업 체크하는 함수
    void printStatus(); // 현재 상태를 출력하는 함수
};

#endif