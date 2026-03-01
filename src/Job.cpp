#include "../include/Job.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// --- Beginner ---
string Beginner::getName() { return "초보자"; }
int Beginner::attack(int level, int weaponDamage, int weaponLevel, int str) {
    int damage = rand() % 10 + 10 + weaponDamage + (weaponLevel * 5) + (str * 2); // 근력 1당 데미지 +2
    cout << "[+" << weaponLevel << " 무기]와 [근력 " << str << "]의 힘으로 " << damage << "의 데미지를 입혔습니다." << endl;
    return damage;
}
int Beginner::magicAttack(int level, int weaponDamage, int intel) {
    int damage = (rand() % 15 + 20 + weaponDamage + (intel * 3)) * 2; // 지능 1당 마법 데미지 증폭
    cout << CYAN << "🔥 파이어볼!! [지능 " << intel << "]의 마력으로 " << damage << "의 데미지를 입혔습니다! (-20 MP)" << RESET << endl;
    return damage;
}

// --- Warrior ---
string Warrior::getName() { return "전사"; }
void Warrior::applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) {
    maxHp += 50; hp = maxHp; weaponDmg += 5;
}
int Warrior::attack(int level, int weaponDamage, int weaponLevel, int str) {
    int damage = rand() % 10 + 10 + weaponDamage + (weaponLevel * 5) + (str * 3); // 전사는 근력 효율이 더 좋음(+3)
    cout << YELLOW << "⚔️ [전사의 일격] [근력 " << str << "]의 파괴력으로 " << damage << "의 데미지를 입혔습니다." << RESET << endl;
    return damage;
}
int Warrior::magicAttack(int level, int weaponDamage, int intel) {
    return Beginner().magicAttack(level, weaponDamage, intel); 
}

// --- Mage ---
string Mage::getName() { return "마법사"; }
void Mage::applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) {
    maxMp += 50; mp = maxMp;
}
int Mage::attack(int level, int weaponDamage, int weaponLevel, int str) {
    return Beginner().attack(level, weaponDamage, weaponLevel, str); 
}
int Mage::magicAttack(int level, int weaponDamage, int intel) {
    int damage = (rand() % 15 + 20 + weaponDamage + (intel * 4)) * 2; // 마법사는 지능 효율 최고
    damage = (int)(damage * 1.5); 
    cout << CYAN << "☄️ [대마법사의 메테오] [지능 " << intel << "]의 거대한 마력으로 " << damage << "의 데미지를 입혔습니다! (-20 MP)" << RESET << endl;
    return damage;
}

// --- Rogue ---
string Rogue::getName() { return "도적"; }
int Rogue::attack(int level, int weaponDamage, int weaponLevel, int str) {
    int damage = rand() % 10 + 10 + weaponDamage + (weaponLevel * 5) + (str * 2);
    int critRoll = rand() % 100;
    if (critRoll < 40) { 
        damage *= 2;
        cout << GREEN << "⚡ [암살자의 일격] 크리티컬!! " << damage << "의 치명상을 입혔습니다!" << RESET << endl;
    } else {
        cout << "[+" << weaponLevel << " 무기]와 [근력 " << str << "]의 힘으로 " << damage << "의 데미지를 입혔습니다." << endl;
    }
    return damage;
}
int Rogue::magicAttack(int level, int weaponDamage, int intel) {
    return Beginner().magicAttack(level, weaponDamage, intel);
}