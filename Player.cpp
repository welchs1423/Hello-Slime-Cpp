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
    maxMp = 50; // ✨ Starts with 50 MP
    mp = 50;
    potions = 3;
    gold = 0;         
    weaponDamage = 0; 
    dungeonFloor = 1; 
}

int Player::attack() {
    int damage = rand() % 10 + 10 + (level * 2) + weaponDamage;
    int critChance = rand() % 100;

    if (critChance < 20) {
        damage *= 2;
        cout << YELLOW << "⚡ CRITICAL HIT!! You pierced the enemy's weak spot for " << damage << " damage!" << RESET << endl;
    } else {
        cout << "You attacked and dealt " << damage << " damage." << endl;
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
    hp -= damage;
    cout << RED << "Enemy counterattacks! You took " << damage << " damage." << RESET << endl;
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
    cout << "Weapon ATK: +" << weaponDamage << " | Dungeon Floor: " << CYAN << dungeonFloor << RESET << endl;
}

void Player::save() {
    ofstream fout("savefile.txt"); 
    if (fout.is_open()) {
        fout << level << " " << exp << " " << maxHp << " " << hp << " " << maxMp << " " << mp << " " << potions << " " << gold << " " << weaponDamage << " " << dungeonFloor;
        fout.close();
        cout << GREEN << "💾 Game saved successfully!" << RESET << endl;
    } else {
        cout << RED << "❌ Failed to create save file." << RESET << endl;
    }
}

bool Player::load() {
    ifstream fin("savefile.txt"); 
    if (fin.is_open()) {
        fin >> level >> exp >> maxHp >> hp >> maxMp >> mp >> potions >> gold >> weaponDamage >> dungeonFloor;
        fin.close();
        cout << GREEN << "📂 Saved game loaded successfully!" << RESET << endl;
        return true;
    } else {
        cout << RED << "❌ No save file found. Starting a new game." << RESET << endl;
        return false;
    }
}