#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Slime.h"
#include "Colors.h" // ✨ Import Color Palette

using namespace std;

void clearScreen() {
    system("cls");
}

int main() {
    system("chcp 65001");
    srand(time(0)); 

    Player player; 
    bool isPlaying = true; 

    clearScreen(); 
    cout << CYAN << "=== Slime Hunter RPG ===" << RESET << endl;
    cout << "1. New Game  2. Continue\nSelect: ";
    int startChoice;
    cin >> startChoice;

    if (startChoice == 2) {
        player.load(); 
    }

    while (isPlaying && player.hp > 0) {
        clearScreen(); 
        cout << "\n=== 🏡 Town Square ===" << endl;
        player.printStatus();
        cout << "1. Enter Dungeon  2. Visit Shop  3. Save Game  4. Quit Game\nSelect: ";
        int townChoice;
        cin >> townChoice;

        if (townChoice == 1) {
            clearScreen(); 
            cout << "\n=== 🏰 Dungeon Floor " << player.dungeonFloor << " ===" << endl;
            
            Slime slime(player.level); 
            bool isBoss = (player.dungeonFloor % 5 == 0); 

            if (isBoss) {
                slime.maxHp *= 3; 
                slime.hp = slime.maxHp;
                slime.baseDamage *= 2; 
                // ✨ Red for Boss Warning
                cout << RED << "🚨 WARNING! A massive KING SLIME (HP: " << slime.hp << ") blocks your path! 🚨" << RESET << endl;
            } else {
                cout << "A wild Slime (HP: " << RED << slime.hp << RESET << ") appeared!" << endl;
            }

            bool inCombat = true;
            while (inCombat && player.hp > 0 && slime.hp > 0) {
                // ✨ Red for Enemy HP
                cout << "\n[Enemy] HP: " << RED << slime.hp << RESET << endl;
                cout << "1. Attack  2. Run  3. Potion (" << player.potions << ")\nSelect: ";
                
                int combatChoice;
                cin >> combatChoice;

                clearScreen(); 

                if (combatChoice == 1) {
                    int damage = player.attack(); 
                    slime.takeDamage(damage);

                    if (slime.hp > 0) {
                        int slimeDamage = slime.attack(); 
                        player.takeDamage(slimeDamage); 
                    }
                } else if (combatChoice == 2) {
                    cout << "You ran away back to town..." << endl;
                    inCombat = false; 
                } else if (combatChoice == 3) {
                    player.heal(); 
                } else {
                    cout << "Invalid input." << endl;
                }
            }

            if (slime.hp <= 0) {
                if (isBoss) {
                    cout << YELLOW << "\n👑 VICTORY! You defeated the KING SLIME!" << RESET << endl;
                    player.gainExp(150); 
                    int earnedGold = rand() % 50 + 50; 
                    player.gold += earnedGold;
                    cout << YELLOW << "💰 Looted " << earnedGold << " Gold from the Boss!" << RESET << endl;
                } else {
                    cout << CYAN << "\n🎉 You defeated the Slime!" << RESET << endl;
                    player.gainExp(50); 
                    int earnedGold = rand() % 20 + 10; 
                    player.gold += earnedGold;
                    cout << YELLOW << "💰 Looted " << earnedGold << " Gold!" << RESET << endl;
                }
                
                player.dungeonFloor++; 
                cout << CYAN << "You found the stairs and advanced to Floor " << player.dungeonFloor << "!" << RESET << endl;
                
                cout << "\nPress Enter to return to town...";
                cin.ignore();
                cin.get(); 
            }

        } else if (townChoice == 2) {
            clearScreen(); 
            cout << CYAN << "\n=== 🛒 Item Shop ===" << RESET << endl;
            player.printStatus();
            cout << "1. Buy Potion (30G)\n2. Buy Iron Sword (+10 ATK) (100G)\n3. Buy Steel Sword (+25 ATK) (250G)\n4. Leave\nSelect: ";
            int shopChoice;
            cin >> shopChoice;

            clearScreen();
            if (shopChoice == 1) {
                if (player.gold >= 30) {
                    player.gold -= 30;
                    player.potions++;
                    cout << GREEN << "Purchased a Potion! (Potions: " << player.potions << ")" << RESET << endl;
                } else cout << RED << "Not enough Gold!" << RESET << endl;
            } else if (shopChoice == 2) {
                if (player.gold >= 100) {
                    player.gold -= 100;
                    player.weaponDamage = 10;
                    cout << GREEN << "Purchased an Iron Sword! Weapon ATK is now +10." << RESET << endl;
                } else cout << RED << "Not enough Gold!" << RESET << endl;
            } else if (shopChoice == 3) {
                if (player.gold >= 250) {
                    player.gold -= 250;
                    player.weaponDamage = 25;
                    cout << GREEN << "Purchased a Steel Sword! Weapon ATK is now +25." << RESET << endl;
                } else cout << RED << "Not enough Gold!" << RESET << endl;
            } else if (shopChoice == 4) {
                cout << "Leaving shop..." << endl;
            } else cout << RED << "Invalid input." << RESET << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();

        } else if (townChoice == 3) {
            clearScreen();
            player.save();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        } else if (townChoice == 4) {
            clearScreen();
            cout << "Quitting game..." << endl;
            isPlaying = false;
        } else {
            clearScreen();
            cout << RED << "Invalid input." << RESET << endl;
        }
    }

    if (player.hp <= 0) cout << RED << "\n💀 The player has fallen... Game Over." << RESET << endl;
    
    return 0;
}