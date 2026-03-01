#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Battle::start(Player& player) {
    system("cls");
    cout << "\n=== 🏰 던전 " << player.dungeonFloor << "층 ===" << endl;

    bool isBoss = (player.dungeonFloor % 5 == 0);
    if (!isBoss) {
        bool eventHappend = DungeonEvent::triggerEvent(player);

        if (player.hp <= 0) {
            return;
        }

        if (eventHappend) {
            player.dungeonFloor++;
            return;
        }
    }

    Monster* enemy = MonsterFactory::spawnMonster(player.dungeonFloor, player.level);

    cout << "야생의 " << RED << enemy->name << RESET << " (이)가 나타났다! (HP: " << RED << enemy->hp << RESET << ")" << endl;

    bool inCombat = true;
    while (inCombat && player.hp > 0 && enemy->hp > 0) {
        cout << "\n[" << CYAN << "플레이어" << RESET << "] 체력: " << GREEN << player.hp << "/" << player.maxHp << RESET 
             << " | 마나: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] 체력: " << RED << enemy->hp << RESET << endl;
        
        // ✨ 전투 메뉴 개편: 기존 포션 단축키들을 지우고 '가방 열기'를 3번에 배치!
        cout << "1. 기본 공격  2. 마법 공격 (20MP)  3. 🎒 가방 열기  4. 도망가기\n선택: ";
        
        int combatChoice;
        cin >> combatChoice;

        system("cls");

        switch (combatChoice) {
            case 1: {
                int damage = player.attack();
                enemy->takeDamage(damage);
                if (enemy->hp > 0) {
                    player.takeDamage(enemy->attack());
                }
                break;
            }
            case 2: {
                int magicDmg = player.magicAttack();
                if (magicDmg != -1) {
                    enemy->takeDamage(magicDmg);
                    if (enemy->hp > 0) {
                        player.takeDamage(enemy->attack());
                    }
                }
                break;
            }
            case 3:
                // ✨ 스카이림 식 먹방: 턴 소모 없이 가방을 열고 정비할 수 있습니다!
                player.openInventory(); 
                break;
            case 4:
                cout << "겁에 질려 마을로 도망쳤습니다..." << endl;
                inCombat = false;
                break;
            default:
                cout << RED << "잘못된 입력입니다." << RESET << endl;
                break;
        }
    }

    if (enemy->hp <= 0) {
        cout << YELLOW << "\n🎉 " << enemy->name << "을(를) 물리쳤습니다!" << RESET << endl;
        
        int expGain = (player.dungeonFloor % 5 == 0) ? 200 : 50;
        player.gainExp(expGain);
        
        int goldGain = (rand() % 30 + 10) + (player.dungeonFloor * 2);
        player.gold += goldGain;
        cout << YELLOW << "💰 " << goldGain << " 골드를 획득했습니다!" << RESET << endl;

        player.dungeonFloor++;
        cout << CYAN << "더 깊은 곳을 향해 " << player.dungeonFloor << "층으로 나아갑니다!" << RESET << endl;
        
        cout << "\n엔터를 누르면 마을로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }

    delete enemy;
}