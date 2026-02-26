#include "../include/Job.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// --- Beginner (초보자) ---
string Beginner::getName() { return "초보자"; }
int Beginner::attack(int level, int weaponDamage, int weaponLevel) {
    int damage = rand() % 10 + 10 + (level * 2) + weaponDamage + (weaponLevel * 5);
    cout << "You attacked with [+" << weaponLevel << " Weapon] and dealt " << damage << " damage." << endl;
    return damage;
}
int Beginner::magicAttack(int level, int weaponDamage) {
    int damage = (rand() % 15 + 20 + (level * 3) + weaponDamage) * 2;
    cout << CYAN << "🔥 FIREBALL!! You cast a magic spell for " << damage << " damage! (-20 MP)" << RESET << endl;
    return damage;
}

// --- Warrior (전사) ---
string Warrior::getName() { return "전사"; }
void Warrior::applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) {
    maxHp += 50; hp = maxHp; weaponDmg += 5;
}
int Warrior::attack(int level, int weaponDamage, int weaponLevel) {
    int damage = rand() % 10 + 10 + (level * 2) + weaponDamage + (weaponLevel * 5);
    cout << YELLOW << "⚔️ [전사의 일격] You attacked with [+" << weaponLevel << " Weapon] and dealt " << damage << " damage." << RESET << endl;
    return damage;
}
int Warrior::magicAttack(int level, int weaponDamage) {
    return Beginner().magicAttack(level, weaponDamage); // 마법은 초보자와 동일
}

// --- Mage (마법사) ---
string Mage::getName() { return "마법사"; }
void Mage::applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) {
    maxMp += 50; mp = maxMp;
}
int Mage::attack(int level, int weaponDamage, int weaponLevel) {
    return Beginner().attack(level, weaponDamage, weaponLevel); // 평타는 초보자와 동일
}
int Mage::magicAttack(int level, int weaponDamage) {
    int damage = (rand() % 15 + 20 + (level * 3) + weaponDamage) * 2;
    damage = (int)(damage * 1.5); // 마법 데미지 1.5배!
    cout << CYAN << "☄️ [대마법사의 메테오] ULTIMATE FIREBALL dealt " << damage << " damage! (-20 MP)" << RESET << endl;
    return damage;
}

// --- Rogue (도적) ---
string Rogue::getName() { return "도적"; }
int Rogue::attack(int level, int weaponDamage, int weaponLevel) {
    int damage = rand() % 10 + 10 + (level * 2) + weaponDamage + (weaponLevel * 5);
    int critRoll = rand() % 100;
    if (critRoll < 40) { // 도적은 크리티컬 40%
        damage *= 2;
        cout << GREEN << "⚡ [암살자의 일격] CRITICAL HIT!! dealt " << damage << " damage!" << RESET << endl;
    } else {
        cout << "You attacked with [+" << weaponLevel << " Weapon] and dealt " << damage << " damage." << endl;
    }
    return damage;
}
int Rogue::magicAttack(int level, int weaponDamage) {
    return Beginner().magicAttack(level, weaponDamage);
}