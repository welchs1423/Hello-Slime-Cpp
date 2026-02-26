#include "Player.h"
#include "Colors.h" 
#include <iostream>
#include <cstdlib>
#include <fstream> 

using namespace std;

Player::Player() {
    level = 1;
    exp = 0;
    maxHp = 100;
    hp = 100;
    maxMp = 50;         // Starts with 50 MP
    mp = 50;
    potions = 3;
    manaPotions = 1;    // 마나 포션 1개 서비스
    gold = 0;         
    weaponDamage = 0; 
    armorDefense = 0;   // Starts with 0 Defense (No armor)
    dungeonFloor = 1;
    weaponLevel = 0;    // 초기 강화 0
    armorLevel = 0;     // 초기 방어구 강화 0
    
    registerStats();    // 생성 시점에 모든 변수 등록
}

void Player::registerStats() {
    // 여기에만 변수를 추가하면 save/load에 자동으로 반영
    stats["level"] = &level;
    stats["exp"] = &exp;
    stats["maxHp"] = &maxHp;
    stats["hp"] = &hp;
    stats["maxMp"] = &maxMp;
    stats["mp"] = &mp;
    stats["potions"] = &potions;
    stats["manaPotions"] = &manaPotions;
    stats["gold"] = &gold;
    stats["weaponDamage"] = &weaponDamage;
    stats["armorDefense"] = &armorDefense;
    stats["dungeonFloor"] = &dungeonFloor;
    stats["weaponLevel"] = &weaponLevel;
    stats["armorLevel"] = &armorLevel;
}

int Player::attack() {
    // 강화 레벨 당 데미지 5씩 추가 가중치
    int bonusDamage = weaponLevel * 5;
    int damage = rand() % 10 + 10 + (level * 2) + weaponDamage + bonusDamage;
    int critChance = rand() % 100;

    if (critChance < 20) {
        damage *= 2;
        cout << YELLOW << "⚡ CRITICAL HIT!! [+" << weaponLevel << " Weapon] dealt " << damage << " damage!" << RESET << endl;
    } else {
        cout << "You attacked with [+" << weaponLevel << " Weapon] and dealt " << damage << " damage." << endl;
    }
    return damage;
}

// ✨ Magic Skill Logic
int Player::magicAttack() {
    if (mp >= 20) {
        mp -= 20; // 마나 20 소모
        int damage = (rand() % 15 + 20 + (level * 3) + weaponDamage) * 2; // 일반 공격보다 훨씬 강력함
        cout << CYAN << "🔥 FIREBALL!! You cast a powerful magic spell for " << damage << " damage! (-20 MP)" << RESET << endl;
        return damage;
    } else {
        cout << RED << "❌ Not enough MP to cast magic!" << RESET << endl;
        return -1; // 마나가 부족하면 -1 반환
    }
}

void Player::takeDamage(int damage) {
    // 강화 1단계당 데미지 3 추가 감소
    int bonusDefense = armorLevel * 3;
    // 방어력(Armor) 적용 로직
    int actualDamage = damage - armorDefense - bonusDefense;
    if(actualDamage < 0) actualDamage = 0;  // 방어력이 너무 높아도 데미지가 마이너스가 되진 않게 처리

    hp -= actualDamage;
    cout << RED << "Enemy attacks! You took " << actualDamage << " damage. (Mitigated " << armorDefense + bonusDefense << " DMG)" << RESET << endl;
}

void Player::heal() {
    if (potions > 0) {
        hp += 30;
        if (hp > maxHp) hp = maxHp;
        potions--;
        cout << GREEN << "You drank a potion! HP recovered. (Potions left: " << potions << ")" << RESET << endl;
    } else {
        cout << RED << "You searched your bag, but you have no potions left!" << RESET << endl;
    }
}

void Player::restoreMp(){
    if(manaPotions > 0){
        mp += 30;
        if(mp > maxMp) mp = maxMp;
        manaPotions--;
        cout << CYAN << "You Drank a Mana Potion! Mp recovered. (Mana Potions left: " << manaPotions << ")" << RESET << endl;
    } else {
        cout << RED << "You searched your bag, but you have no mana potions left!" << RESET << endl;
    }
}

void Player::gainExp(int amount) {
    exp += amount;
    cout << CYAN << "Gained " << amount << " EXP." << RESET << endl;

    if (exp >= 100) {
        level++;
        exp -= 100;
        maxHp += 20;
        hp = maxHp;
        maxMp += 10; // 레벨업 시 최대 마나 증가
        mp = maxMp;  // 마나 풀 회복
        potions++;
        cout << YELLOW << "✨ LEVEL UP! You are now Lv." << level << "! (Max HP/MP increased, fully restored, gained 1 Potion)" << RESET << endl;
    }
}

void Player::printStatus() {
    cout << "\n[" << CYAN << "Lv." << level << " Player" << RESET << "] "
         << "HP: " << GREEN << hp << "/" << maxHp << RESET
         << " | MP: " << CYAN << mp << "/" << maxMp << RESET // ✨ Display MP
         << " | EXP: " << CYAN << exp << "/100" << RESET
         << " | Gold: " << YELLOW << gold << "G" << RESET << endl;
    cout << "Weapon ATK: +" << weaponDamage << " | Armor DEF: +" << armorDefense << " | Dungeon Floor: " << CYAN << dungeonFloor << RESET << endl;
    cout << "Items: [HP Potion x" << potions << "] [MP Potion x" << manaPotions << "]" << endl;
}

void Player::save() {
    ofstream fout("savefile.txt");
    if (fout.is_open()){
        // 리스트를 돌면서 이름 값 형태로 저장
        for(auto const& [name, ptr] : stats){
            fout << name << " " << *ptr << endl;
        }
        fout.close();
        cout << "Game saved automatically!" << endl;
    }
}

bool Player::load() {
    ifstream fin("savefile.txt");
    if(fin.is_open()){
        string name;
        int value;
        // 파일에서 이름을 읽고, 그 이름에 해당하는 주소에 값을 넣음
        while (fin >> name >> value){
            if (stats.find(name) != stats.end()){
                *(stats[name]) = value;
            }
        }
        fin.close();
        cout << "All stats loaded successfully!" << endl;
        return true;
    }
    return false;
}