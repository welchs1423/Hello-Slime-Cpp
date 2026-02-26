#include "Player.h"
#include "Colors.h" // ✨ Import Color Palette
#include <iostream>
#include <cstdlib>
#include <fstream> 

using namespace std;

Player::Player() {
    level = 1;
    exp = 0;
    maxHp = 100;
    hp = 100;
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
        // ✨ Yellow for Critical Hits
        cout << YELLOW << "⚡ CRITICAL HIT!! You pierced the enemy's weak spot for " << damage << " damage!" << RESET << endl;
    } else {
        cout << "You attacked and dealt " << damage << " damage." << endl;
    }
    return damage;
}

void Player::takeDamage(int damage) {
    hp -= damage;
    // ✨ Red for taking damage
    cout << RED << "Enemy counterattacks! You took " << damage << " damage." << RESET << endl;
}

void Player::heal() {
    if (potions > 0) {
        hp += 30;
        if (hp > maxHp) hp = maxHp;
        potions--;
        // ✨ Green for healing
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
        potions++;
        // ✨ Yellow for Level Up
        cout << YELLOW << "✨ LEVEL UP! You are now Lv." << level << "! (Max HP increased, HP fully restored, gained 1 Potion)" << RESET << endl;
    }
}

void Player::printStatus() {
    // ✨ Colorful Status UI
    cout << "\n[" << CYAN << "Lv." << level << " Player" << RESET << "] "
         << "HP: " << GREEN << hp << "/" << maxHp << RESET
         << " | EXP: " << CYAN << exp << "/100" << RESET
         << " | Gold: " << YELLOW << gold << "G" << RESET << endl;
    cout << "Weapon ATK: +" << weaponDamage << " | Dungeon Floor: " << CYAN << dungeonFloor << RESET << endl;
}

void Player::save() {
    ofstream fout("savefile.txt"); 
    if (fout.is_open()) {
        fout << level << " " << exp << " " << maxHp << " " << hp << " " << potions << " " << gold << " " << weaponDamage << " " << dungeonFloor;
        fout.close();
        cout << GREEN << "💾 Game saved successfully!" << RESET << endl;
    } else {
        cout << RED << "❌ Failed to create save file." << RESET << endl;
    }
}

bool Player::load() {
    ifstream fin("savefile.txt"); 
    if (fin.is_open()) {
        fin >> level >> exp >> maxHp >> hp >> potions >> gold >> weaponDamage >> dungeonFloor;
        fin.close();
        cout << GREEN << "📂 Saved game loaded successfully!" << RESET << endl;
        return true;
    } else {
        cout << RED << "❌ No save file found. Starting a new game." << RESET << endl;
        return false;
    }
}