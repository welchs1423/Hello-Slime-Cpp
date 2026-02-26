#include "Battle.h"
#include "Monster.h"
#include "Slime.h"
#include "Goblin.h"
#include "Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Battle::start(Player& player) {
    system("cls");
    cout << "\n=== 🏰 Dungeon Floor " << player.dungeonFloor << " ===" << endl;

    // 1️⃣ 보스 여부 확인 (5층 단위)
    bool isBoss = (player.dungeonFloor % 5 == 0);
    
    // 2️⃣ 몬스터 생성 (다형성 활용)
    Monster* enemy = nullptr;

    if (isBoss) {
        // 보스는 더 강력한 스탯을 가진 'King Slime'으로 생성
        enemy = new Monster("KING SLIME", 200 + (player.level * 20), 15 + player.level);
        cout << RED << "WARNING! A massive " << enemy->name << " blocks your path!" << RESET << endl;
    } else {
        // 일반 층: 3층 단위로 고블린, 그 외에는 슬라임 등장
        if (player.dungeonFloor % 3 == 0) {
            enemy = new Goblin(player.level);
        } else {
            enemy = new Slime(player.level);
        }
        cout << "A wild " << RED << enemy->name << RESET << " (HP: " << RED << enemy->hp << RESET << ") appeared!" << endl;
    }

    // 3️⃣ 전투 루프
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
            // 일반 공격
            int damage = player.attack();
            enemy->takeDamage(damage);
            
            if (enemy->hp > 0) {
                player.takeDamage(enemy->attack());
            }
        } else if (combatChoice == 2) {
            // 마법 공격
            int magicDmg = player.magicAttack();
            if (magicDmg != -1) {
                enemy->takeDamage(magicDmg);
                if (enemy->hp > 0) {
                    player.takeDamage(enemy->attack());
                }
            }
        } else if (combatChoice == 3) {
            // 도망가기
            cout << "You ran away back to town..." << endl;
            inCombat = false;
        } else if (combatChoice == 4) {
            // HP 회복
            player.heal();
        } else if (combatChoice == 5) {
            // MP 회복
            player.restoreMp();
        } else {
            cout << "Invalid input." << endl;
        }
    }

    // 4️⃣ 전투 결과 처리
    if (enemy->hp <= 0) {
        if (isBoss) {
            cout << YELLOW << "\n👑 VICTORY! You defeated the " << enemy->name << "!" << RESET << endl;
            player.gainExp(200); // 보스 경험치
            int earnedGold = rand() % 100 + 100; // 보스 골드
            player.gold += earnedGold;
            cout << YELLOW << "💰 Looted " << earnedGold << " Gold from the Boss!" << RESET << endl;
        } else {
            cout << CYAN << "\n🎉 You defeated the " << enemy->name << "!" << RESET << endl;
            player.gainExp(50);
            int earnedGold = rand() % 30 + 10;
            player.gold += earnedGold;
            cout << YELLOW << "💰 Looted " << earnedGold << " Gold!" << RESET << endl;
        }
        
        player.dungeonFloor++;
        cout << CYAN << "You found the stairs and advanced to Floor " << player.dungeonFloor << "!" << RESET << endl;
        
        cout << "\nPress Enter to return to town...";
        cin.ignore();
        cin.get();
    }

    // new로 생성한 몬스터 객체를 삭제하여 메모리 누수 방지
    delete enemy;
}