#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Battle::start(Player& player) {
    // 층수 출력
    system("cls");
    cout << "\n=== 🏰 던전 " << player.dungeonFloor << "층 ===" << endl;

    // 보스전이 아닐 때만 30% 확률로 던전 이벤트 발생
    bool isBoss = (player.dungeonFloor % 5 == 0);
    if (!isBoss) {
        bool eventHappend = DungeonEvent::triggerEvent(player);

        // 이벤트에서 죽었으면 전투 없이 마을로 강제 귀환
        if (player.hp <= 0) {
            return;
        }

        // 이벤트가 발생했으면, 몬스터 조우 없이 층수만 올라감 (이벤트 자체가 하나의 층 탐험으로 간주)
        if (eventHappend) {
            player.dungeonFloor++;
            return;
        }
    }

    // 팩토리에게 몬스터 생성을 전적으로 맡김
    Monster* enemy = MonsterFactory::spawnMonster(player.dungeonFloor, player.level);

    cout << "야생의 " << RED << enemy->name << RESET << " (이)가 나타났다! (HP: " << RED << enemy->hp << RESET << ")" << endl;

    bool inCombat = true;
    while (inCombat && player.hp > 0 && enemy->hp > 0) {
        cout << "\n[" << CYAN << "플레이어" << RESET << "] 체력: " << GREEN << player.hp << "/" << player.maxHp << RESET 
             << " | 마나: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] 체력: " << RED << enemy->hp << RESET << endl;
        
        cout << "1. 기본 공격  2. 마법 공격 (20MP)  3. 도망가기  4. 체력 포션 (" << player.potions << ")  5. 마나 포션 (" << player.manaPotions << ")\n선택: ";
        
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
                cout << "겁에 질려 마을로 도망쳤습니다..." << endl;
                inCombat = false;
                break;
            case 4:
                player.heal();
                break;
            case 5:
                player.restoreMp();
                break;
            default:
                cout << RED << "잘못된 입력입니다." << RESET << endl;
                break;
        }
    }

    if (enemy->hp <= 0) {
        cout << YELLOW << "\n🎉 " << enemy->name << "을(를) 물리쳤습니다!" << RESET << endl;
        
        // 경험치 및 골드 보상
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