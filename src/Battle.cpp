#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Battle::start(Player& player) {
    system("cls");
    cout << "\n=== 🏰 Dungeon Floor " << player.dungeonFloor << " ===" << endl;

    // ✨ 팩토리에게 몬스터 생성을 전적으로 맡깁니다.
    Monster* enemy = MonsterFactory::spawnMonster(player.dungeonFloor, player.level);

    cout << "A wild " << RED << enemy->name << RESET << " (HP: " << RED << enemy->hp << RESET << ") appeared!" << endl;

    bool inCombat = true;
    while (inCombat && player.hp > 0 && enemy->hp > 0) {
        cout << "\n[" << CYAN << "Player" << RESET << "] HP: " << GREEN << player.hp << "/" << player.maxHp << RESET 
             << " | MP: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] HP: " << RED << enemy->hp << RESET << endl;
        
        cout << "1. Attack  2. Magic (20MP)  3. Run  4. HP Potion (" << player.potions << ")  5. MP Potion (" << player.manaPotions << ")\nSelect: ";
        
        int combatChoice;
        cin >> combatChoice;

        system("cls");

        if (combatChoice == 1) {
            int damage = player.attack();
            enemy->takeDamage(damage);
            if (enemy->hp > 0) {
                player.takeDamage(enemy->attack());
            }
        } else if (combatChoice == 2) {
            int magicDmg = player.magicAttack();
            if (magicDmg != -1) {
                enemy->takeDamage(magicDmg);
                if (enemy->hp > 0) {
                    player.takeDamage(enemy->attack());
                }
            }
        } else if (combatChoice == 3) {
            cout << "You ran away back to town..." << endl;
            inCombat = false;
        } else if (combatChoice == 4) {
            player.heal();
        } else if (combatChoice == 5) {
            player.restoreMp();
        } else {
            cout << "Invalid input." << endl;
        }
    }

    if (enemy->hp <= 0) {
        cout << YELLOW << "\n🎉 You defeated the " << enemy->name << "!" << RESET << endl;
        
        // 경험치 및 골드 보상 (나중에 이 부분도 Monster 클래스 안으로 넣으면 더 깔끔합니다)
        int expGain = (player.dungeonFloor % 5 == 0) ? 200 : 50;
        player.gainExp(expGain);
        
        int goldGain = (rand() % 30 + 10) + (player.dungeonFloor * 2);
        player.gold += goldGain;
        cout << YELLOW << "💰 Looted " << goldGain << " Gold!" << RESET << endl;

        player.dungeonFloor++;
        cout << CYAN << "You advanced to Floor " << player.dungeonFloor << "!" << RESET << endl;
        
        cout << "\nPress Enter to return to town...";
        cin.ignore();
        cin.get();
    }

    delete enemy;
}