#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

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

// 게임 저장하기 (파일 쓰기)
void Player::save(){
    ofstream fout("savefile.txt");
    if(fout.is_open()){
        fout << level << " " << exp << " " << maxHp << " " << hp << " " << potions;
        fout.close();
        cout << "게임이 성공적으로 저장되었습니다!" << endl;
    } else {
        cout << "저장 파일을 생성하는데 실패했습니다." << endl;
    }
}

// 게임 불러오기 (파일 읽기)
bool Player::load(){
    ifstream fin("savefile.txt");
    if(fin.is_open()){
        fin >> level >> exp >> maxHp >> hp >> potions;
        fin.close();
        cout << "저장된 게임을 성공적으로 불러왔습니다!" << endl;
        return true;
    } else {
        cout << "저장된 파일이 없습니다. 새로 시작합니다." << endl;
        return false;
    }
}