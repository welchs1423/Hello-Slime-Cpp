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
        if (player.hp <= 0) return;
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
        
        cout << "1. 기본 공격  2. 마법 공격 (20MP)  3. 🎒 가방 열기  4. 도망가기\n선택: ";
        
        int combatChoice;
        cin >> combatChoice;

        system("cls");

        switch (combatChoice) {
            case 1: {
                int damage = player.attack();
                enemy->takeDamage(damage);
                if (enemy->hp > 0) player.takeDamage(enemy->attack());
                break;
            }
            case 2: {
                int magicDmg = player.magicAttack();
                if (magicDmg != -1) {
                    enemy->takeDamage(magicDmg);
                    if (enemy->hp > 0) player.takeDamage(enemy->attack());
                }
                break;
            }
            case 3:
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
        
        // 1번, 2번 토벌 퀘스트 체크
        if (player.activeQuestId == 1 && enemy->name == "초록 고블린") {
            player.questProgress++;
            cout << YELLOW << "[📜 퀘스트] 초록 고블린 토벌 진행도: " << player.questProgress << "/3" << RESET << endl;
        } else if (player.activeQuestId == 2 && enemy->name == "푸른 슬라임") {
            player.questProgress++;
            cout << YELLOW << "[📜 퀘스트] 푸른 슬라임 토벌 진행도: " << player.questProgress << "/5" << RESET << endl;
        }
        
        int expGain = (player.dungeonFloor % 5 == 0) ? 200 : 50;
        player.gainExp(expGain);
        
        int goldGain = (rand() % 30 + 10) + (player.dungeonFloor * 2);
        player.gold += goldGain;
        cout << YELLOW << "💰 " << goldGain << " 골드를 획득했습니다!" << RESET << endl;

        player.dungeonFloor++;
        cout << CYAN << "더 깊은 곳을 향해 " << player.dungeonFloor << "층으로 나아갑니다!" << RESET << endl;
        
        if (player.activeQuestId == 3 && player.dungeonFloor >= 5) {
            player.questProgress = 1; // 달성 완료!
            cout << YELLOW << "[📜 퀘스트] 던전 5층 도달 임무 완료! 길드로 돌아가 보상을 받으세요." << RESET << endl;
        }
        
        cout << "\n엔터를 누르면 마을로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }

    delete enemy;
}