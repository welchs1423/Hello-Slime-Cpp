#include "Player.h"
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
    gold = 0;   // Starts with 0 Gold
    weaponDamage = 0;   // Starts with bare hands
    dungeonFloor = 1;   // Starts at Floor 1
}

int Player::attack() {
    // Basic damage + level scailing + weapon damage
    int damage = rand() % 10 + 10 + (level * 2) + weaponDamage;
    int critChance = rand() % 100;

    if (critChance < 20) {
        damage *= 2;
        cout << "CRITICAL HIT!! You pierced the slime's weak spot for " << damage << " damage!" << endl;
    } else {
        cout << "You attacked the slime and dealt " << damage << " damage." << endl;
    }
    return damage;
}

void Player::takeDamage(int damage) {
    hp -= damage;
    cout << "Slime counterattacks! You took " << damage << " damage." << endl;
}

void Player::heal() {
    if (potions > 0) {
        hp += 30;
        if (hp > maxHp) hp = maxHp;
        potions--;
        cout << "You drank a potion! HP recovered. (Potions left: " << potions << ")" << endl;
    } else {
        cout << "You searched your bag, but you have no potions left!" << endl;
    }
}

void Player::gainExp(int amount) {
    exp += amount;
    cout << "Gained " << amount << " EXP." << endl;

    if (exp >= 100) {
        level++;
        exp -= 100;
        maxHp += 20;
        hp = maxHp;
        potions++;
        cout << "LEVEL UP! You are now Lv." << level << "! (Max HP increased, HP fully restored, gained 1 Potion)" << endl;
    }
}

void Player::printStatus() {
    // Display Gold and Weapon Damage
    cout << "\n[Lv." << level << " Player] HP: " << hp << "/" << maxHp
        << " | EXP: " << exp << "/100 | Gold: " << gold << "G" << endl;
    // Display Floor
    cout << "Weapon ATK: +" << weaponDamage << "| Dungeon FLoor: " << dungeonFloor << endl; 
}

void Player::save() {
    ofstream fout("savefile.txt"); 
    if (fout.is_open()) {
        fout << level << " " << exp << " " << maxHp << " " << hp << " " << potions << gold << " " << weaponDamage << " " << dungeonFloor;
        fout.close();
        cout << "Game saved successfully!" << endl;
    } else {
        cout << "Failed to create save file." << endl;
    }
}

bool Player::load() {
    ifstream fin("savefile.txt"); 
    if (fin.is_open()) {
        fin >> level >> exp >> maxHp >> hp >> potions >> gold >> weaponDamage >> dungeonFloor;
        fin.close();
        cout << "Saved game loaded successfully!" << endl;
        return true;
    } else {
        cout << "No save file found. Starting a new game." << endl;
        return false;
    }
}