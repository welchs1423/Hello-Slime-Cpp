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
    bool isPlaying = true;  // Controls the main game loop

    cout << "=== Slime Hunter RPG ===" << endl;
    cout << "1. New Game  2. Continue\nSelect: ";
    int startChoice;
    cin >> startChoice;

    if (startChoice == 2) {
        player.load(); 
    }

    cout << "\n=== Entered the Endless Slime Dungeon! ===" << endl;

    // Town Loop
    while (isPlaying && player.hp > 0) {
        cout << "\n=== Town Square ===" << endl;
        player.printStatus();
        cout << "1. Enter Dungeon 2. Visit Shop 3. Save Game 4. Quit Game\nSelect: ";
        int townChoice;
        cin >> townChoice;
        
        if(townChoice == 1){
            // Dungeon Phase
            cout << "\n=== Dungeon Floor " << player.dungeonFloor << " ===" << endl;

            Slime slime(player.level);
            bool isBoss = (player.dungeonFloor % 5 == 0);   // 5층마다 보스 등장

            if(isBoss){
                slime.maxHp *= 3; // 체력 3배
                slime.hp = slime.maxHp;
                slime.baseDamage *= 2; // 공격력 2배
                cout << "WARNING! A massive KING SLIME (HP: " << slime.hp << ") blocks your path!" << endl;
            } else {
                cout << "A wild Slime (HP: " << slime.hp << ") appeared!" << endl;
            }

            bool inCombat = true;
            while(inCombat && player.hp > 0 && slime.hp > 0){
                cout << "\n[Slime] Hp: " << slime.hp << endl;
                cout << "1. Attack 2. Run 3. Potion (" << player.potions << ")\nSelect: ";

                int combatChoice;
                cin >> combatChoice;

                if(combatChoice == 1){
                    int damage = player.attack();
                    slime.takeDamage(damage);

                    if (slime.hp > 0){
                        int slimeDamage = slime.attack();
                        player.takeDamage(slimeDamage);
                    }
                } else if(combatChoice == 2){
                    cout << "Youi ran away back to town..." << endl;
                    inCombat = false; // Exits combat, returns to town
                } else if(combatChoice == 3){
                    player.heal();
                } else {
                    cout << "invalid input." << endl;
                }
            }

            if(slime.hp <= 0){
                if(isBoss){
                    cout << "\n VICTORY! You defeated the KING SLIME!" << endl;
                    player.gainExp(150); // 보스 경험치
                    int earnedGold = rand() % 50 + 50;  // 보스 골드 (50~99)
                    player.gold += earnedGold;
                    cout << "Looted " << earnedGold << " Gold from the Boss!" << endl;
                } else {
                    cout << "\n You defeated the Slime!" << endl;
                    player.gainExp(50);
                    int earnedGold = rand() % 20 + 10;
                    player.gold += earnedGold;
                    cout << "Looted " << earnedGold << " Gold!" << endl;
                }

                player.dungeonFloor++; // 다음 층으로 이동
                cout << "You font the stairs and advanced to Floor " << player.dungeonFloor << "!" << endl;
            }
        } else if (townChoice == 2){
            // Shop Phase
            cout << "\n === Item Shop ===" << endl;
            cout << "1. Buy Potion (30G) 2. Buy Iron Sword (+10 ATK) (100G) 3. Leave\nSelect: ";
            int shopChoice;
            cin >> shopChoice;

            if(shopChoice == 1){
                if(player.gold >= 30){
                    player.gold -= 30;
                    player.potions++;
                    cout << "Purchased a Potion! (Potions : " << player.potions << ")" << endl;
                } else cout << "Not enough Gold!" << endl;
            } else if(shopChoice == 2){
                if(player.gold >= 100){
                    player.gold -= 100;
                    player.weaponDamage = 10;
                    cout << "Purchased an Iron Sword! Weapon ATK is now +10." << endl;
                }else cout << "Not enough Gold!" << endl;
            } else if(shopChoice == 3){
                cout << "Leaving shop..." << endl;
            } else cout << "invalid input." << endl;
        } else if (townChoice == 3){
            player.save();
        } else if (townChoice == 4){
            cout << "Quitting game..." << endl;
            isPlaying = false;
        } else {
            cout << "invalid input." << endl;
        }
    }
    
    if(player.hp <= 0) cout <<"\n The player has fallen... Game Over." << endl;

    return 0;
}

