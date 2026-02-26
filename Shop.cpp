#include "Shop.h"
#include "Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Shop::visit(Player& player) {
    system("cls");
    cout << CYAN << "\n=== 🛒 Item Shop ===" << RESET << endl;
    player.printStatus();
    cout << "1. Buy Potion (30G)\n";
    cout << "2. Buy Mana Potion (30G)\n";   // 신상 입고
    cout << "3. Buy Iron Sword (+10 ATK) (100G)\n";
    cout << "4. Buy Steel Sword (+25 ATK) (250G)\n";
    cout << "5. Buy Leather Armor (+5 DEF) (80G)\n";
    cout << "6. Buy Iron Armor (+15 DEF) (200G)\n";
    cout << "7. Leave\nSelect: ";
    int shopChoice;
    cin >> shopChoice;

    system("cls");
    if (shopChoice == 1) {
        if (player.gold >= 30) {
            player.gold -= 30;
            player.potions++;
            cout << GREEN << "Purchased a Potion! (Potions: " << player.potions << ")" << RESET << endl;
        } else cout << RED << "Not enough Gold!" << RESET << endl;
    } else if (shopChoice == 2){
        if(player.gold >= 30){
            player.gold -= 30;
            player.manaPotions++;
            cout << CYAN << "Purchased a Mana Potion!" << RESET << endl;
        }else cout << RED << "Not enough Gold!" << RESET << endl;
    } else if (shopChoice == 3) {
        if (player.gold >= 100) {
            player.gold -= 100;
            player.weaponDamage = 10;
            cout << GREEN << "Purchased an Iron Sword! Weapon ATK is now +10." << RESET << endl;
        } else cout << RED << "Not enough Gold!" << RESET << endl;
    } else if (shopChoice == 4) {
        if (player.gold >= 250) {
            player.gold -= 250;
            player.weaponDamage = 25;
            cout << GREEN << "Purchased a Steel Sword! Weapon ATK is now +25." << RESET << endl;
        } else cout << RED << "Not enough Gold!" << RESET << endl;
    } else if (shopChoice == 5) {
        if (player.gold >= 80) {
            player.gold -= 80;
            player.armorDefense = 5;
            cout << GREEN << "Purchased Leather Armor! Armor DEF is now +5." << RESET << endl;
        } else cout << RED << "Not enough Gold!" << RESET << endl;
    } else if (shopChoice == 6) {
        if (player.gold >= 200) {
            player.gold -= 200;
            player.armorDefense = 15;
            cout << GREEN << "Purchased Iron Armor! Armor DEF is now +15." << RESET << endl;
        } else cout << RED << "Not enough Gold!" << RESET << endl;
    } else if (shopChoice == 7) {
        cout << "Leaving shop..." << endl;
    } else cout << RED << "Invalid input." << RESET << endl;
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}