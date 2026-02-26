#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Slime.h"

using namespace std;

int main() {
    // Keeps UTF-8 encoding just in case
    system("chcp 65001");
    srand(time(0)); 

    Player player; 

    cout << "=== Slime Hunter RPG ===" << endl;
    cout << "1. New Game  2. Continue\nSelect: ";
    int startChoice;
    cin >> startChoice;

    if (startChoice == 2) {
        player.load(); 
    }

    cout << "\n=== Entered the Endless Slime Dungeon! ===" << endl;

    while (player.hp > 0) {
        Slime slime(player.level); 
        
        cout << "\n=========================================" << endl;
        cout << "A wild Slime (HP: " << slime.hp << ") appeared!" << endl;

        while (player.hp > 0 && slime.hp > 0) {
            player.printStatus(); 
            cout << "[Slime] HP: " << slime.hp << endl;
            cout << "1. Attack  2. Run  3. Potion (" << player.potions << ")  4. Save\nSelect: ";
            
            int choice;
            cin >> choice;

            if (choice == 1) {
                int damage = player.attack(); 
                slime.takeDamage(damage);

                if (slime.hp > 0) {
                    int slimeDamage = slime.attack(); 
                    player.takeDamage(slimeDamage); 
                }
            } else if (choice == 2) {
                cout << "You successfully ran away... Leaving the dungeon." << endl;
                return 0; 
            } else if (choice == 3) {
                player.heal(); 
            } else if (choice == 4) {
                player.save(); 
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        }

        if (slime.hp <= 0) {
            cout << "\n🎉 You defeated the Slime!" << endl;
            player.gainExp(50); 
        }
    }

    if (player.hp <= 0) cout << "\n💀 The player has fallen... Game Over." << endl;
    
    return 0;
}