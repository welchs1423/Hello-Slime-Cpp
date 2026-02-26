#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// 1. 초기 스탯 세팅
Player::Player() {
    level = 1;
    exp = 0;
    maxHp = 100;
    hp = 100;
    potions = 3;
}

// 2. 공격 로직 (치명타 포함)
int Player::attack(){
    int damage = rand() % 10 + 10 + (level * 2);
    int critChance = rand() % 100;

    if (critChance < 20){
        damage *= 2;
        cout << "크리티컬 히트!! 슬라임의 급소를 찔러 " << damage << "의 피해를 입혔습니다!" << endl;
    } else {
        cout << "슬라임을 공격해서 " << damage << "의 피해를 입혔습니다." << endl;
    }
    return damage;   // 계산된 데미지를 밖으로 던져줌
}

// 3. 피해 입기 로직
void Player::takeDamage(int damage){
    hp -= damage;
    cout << "슬라임의 반격! " << damage << "의 피해를 입었습니다." << endl;
}

// 4. 회복 로직
void Player::heal(){
    if(potions > 0){
        hp += 30;
        if (hp > maxHp) hp = maxHp;
        potions--;
        cout << "물약을 마셨습니다! HP가 회복되었습니다. (남은 물약: )" << potions << ")" << endl;
    } else {
        cout << "가방을 뒤져보았지만, 물약이 없습니다!" << endl;
    }
}

// 5. 경험치 및 레벨업 로직
void Player::gainExp(int amount){
    exp += amount;
    cout << "경험치를 " << amount << " 획득했습니다." << endl;

    if(exp >= 100){
        level++;
        exp -= 100;
        maxHp += 20;
        hp = maxHp;
        potions++;
        cout << "레벨업! Lv." << level << "이 되었습니다! (최대 체력 증가, HP 모두 회복, 물약 1개 획득)" << endl;
    }
}

// 6. 상태 출력 로직
void Player::printStatus(){
    cout << "\n[Lv. " << level << " 플레이어] HP: " << hp << "/" << maxHp << "|EXP: " << exp << "/100" << endl;
}