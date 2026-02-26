#include "Battle.h"
#include "Slime.h"
#include "Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Battle::start(Player& player) {
    system("cls");
    cout << "\n=== 🏰 Dungeon Floor " << player.dungeonFloor << " ===" << endl;
    
    Slime slime(player.level);
    bool isBoss = (player.dungeonFloor % 5 == 0);

    if (isBoss) {
        slime.maxHp *= 3;
        slime.hp = slime.maxHp;
        slime.baseDamage *= 2;
        cout << RED << "🚨 WARNING! A massive KING SLIME (HP: " << slime.hp << ") blocks your path! 🚨" << RESET << endl;
    } else {
        cout << "A wild Slime (HP: " << RED << slime.hp << RESET << ") appeared!" << endl;
    }

    bool inCombat = true;
    while (inCombat && player.hp > 0 && slime.hp > 0) {
        cout << "\n[" << CYAN << "Player" << RESET << "] HP: " << GREEN << player.hp << "/" << player.maxHp << RESET
             << " | MP: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[Enemy] HP: " << RED << slime.hp << RESET << endl;
        
        cout << "1. Attack  2. Magic (20MP)  3. Run  4. Potion (" << player.potions << ")\nSelect: ";
        
        int combatChoice;
        cin >> combatChoice;

        system("cls");

        if (combatChoice == 1) {
            int damage = player.attack();
            slime.takeDamage(damage);
            if (slime.hp > 0) {
                int slimeDamage = slime.attack();
                player.takeDamage(slimeDamage);
            }
        } else if (combatChoice == 2) {
            int magicDmg = player.magicAttack();
            if (magicDmg != -1) {
                slime.takeDamage(magicDmg);
                if (slime.hp > 0) {
                    int slimeDamage = slime.attack();
                    player.takeDamage(slimeDamage);
                }
            }
        } else if (combatChoice == 3) {
            cout << "You ran away back to town..." << endl;
            inCombat = false;
        } else if (combatChoice == 4) {
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
}