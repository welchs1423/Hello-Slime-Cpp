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
    cout << "7. [Upgrade Weapon] (+5 ATK) (50G)\n"; // 신규 메뉴

    // 신규 메뉴 추가
    cout << "8. 🎁 Buy Mystery Box (50G) - Test your luck!\n"; 
    cout << "9. Leave\nSelect: ";
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
    } else if (shopChoice == 7){
        if (player.gold >= 50) {
            player.gold -= 50;
            player.weaponLevel++;
            cout << YELLOW << "Weapon Upgraded! Current: +" << player.weaponLevel << RESET << endl;
        } else {
            cout << RED << "Not enough Gold for upgrade!" << RESET << endl;
        }
    } else if (shopChoice == 8){
        if(player.gold >= 50){
            player.gold -= 50;
            cout << YELLOW << "Opening the Mystery Box..." << RESET << endl;

            int roll = rand() % 100; // 0~99 랜덤 뽑기

            if(roll < 10){
                // 10% 확률: 대박! (200 골드 당첨)
                cout << YELLOW << "JACKPOT! You found 200 Gold!" << RESET << endl;
                player.gold += 200;
            } else if (roll < 40){
                // 30% 확률: 중박! (포션 세트)
                cout << GREEN << "You found 2 HP Potions and 1 MP Potion!" << RESET << endl;
                player.potions += 2;
                player.manaPotions += 1;
            } else if (roll< 70){
                // 30% 확률: 소박! (무기 1강 무료)
                cout << CYAN << "A magical hammer strikes! Weapon Level +1!" << RESET << endl;
                player.weaponLevel++;
            } else {
                // 30% 확률 꽝!
                cout << RED << "It's just a pile of rocks... Better luck next time." << RESET << endl;
            }
        } else {
            cout << RED << "Not enough Gold for the Mystery Box!" << RESET << endl;
        }
    } else if (shopChoice == 9) {
        cout << "Leaving shop..." << endl;
    } else cout << RED << "Invalid input." << RESET << endl;
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}