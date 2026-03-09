#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <memory>

using namespace std;

void Battle::start(Player &player, int difficulty)
{
    system("cls");

    float statMultiplier = 1.0f;
    float rewardMultiplier = 1.0f;
    string diffName = "보통";

    if (difficulty == 1)
    {
        statMultiplier = 0.8f;
        rewardMultiplier = 0.8f;
        diffName = "쉬움";
    }
    else if (difficulty == 3)
    {
        statMultiplier = 1.5f;
        rewardMultiplier = 1.5f;
        diffName = "어려움";
    }

    cout << "\n=== 던전 " << player.dungeonFloor << "층 [" << diffName << "] ===" << endl;

    bool isBoss = (player.dungeonFloor % 5 == 0);
    if (!isBoss)
    {
        bool eventHappend = DungeonEvent::triggerEvent(player);
        if (player.hp <= 0)
            return;
        if (eventHappend)
        {
            player.dungeonFloor++;
            return;
        }
    }

    // 스마트 포인터로 몬스터 객체 래핑 (함수 종료 시 자동 메모리 해제)
    std::unique_ptr<Monster> enemy(MonsterFactory::spawnMonster(player.dungeonFloor, player.level));

    enemy->hp = (int)(enemy->hp * statMultiplier);

    cout << "야생의 " << RED << enemy->name << RESET << " (이)가 나타났다! (HP: " << RED << enemy->hp << RESET << ")" << endl;

    bool inCombat = true;
    while (inCombat && player.hp > 0 && enemy->hp > 0)
    {
        cout << "\n[플레이어] 체력: " << GREEN << player.hp << "/" << player.maxHp << RESET
             << " | 마나: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] 체력: " << RED << enemy->hp << RESET << endl;

        cout << "1. 기본 공격  2. 스킬북 펼치기  3. 가방 열기  4. 도망가기\n선택: ";

        int combatChoice;
        cin >> combatChoice;
        system("cls");

        switch (combatChoice)
        {
        case 1:
        {
            int damage = player.attack();
            enemy->takeDamage(damage);
            if (enemy->hp > 0)
            {
                player.takeDamage((int)(enemy->attack() * statMultiplier));
            }
            break;
        }
        case 2:
        {
            if (player.skills.empty())
            {
                cout << RED << "배운 스킬이 없습니다!" << RESET << endl;
                break;
            }

            cout << "\n=== 스킬북 ===" << endl;
            for (size_t i = 0; i < player.skills.size(); ++i)
            {
                cout << i + 1 << ". [" << player.skills[i].getTypeName() << "] "
                     << YELLOW << player.skills[i].name << RESET
                     << " (소모 MP: " << CYAN << player.skills[i].mpCost << RESET
                     << " / 위력: " << player.skills[i].baseDamage << ")" << endl;
            }
            cout << "0. 취소\n사용할 스킬 번호를 선택하세요: ";

            int skillChoice;
            cin >> skillChoice;

            if (skillChoice == 0)
                break;

            if (skillChoice > 0 && skillChoice <= player.skills.size())
            {
                Skill &selectedSkill = player.skills[skillChoice - 1];

                if (player.mp >= selectedSkill.mpCost)
                {
                    player.mp -= selectedSkill.mpCost;

                    int damage = 0;
                    if (selectedSkill.type == 1)
                    {
                        damage = (rand() % 10 + selectedSkill.baseDamage + player.weaponDamage + (player.weaponLevel * 5)) + (player.str * 3);
                        cout << YELLOW << "[" << selectedSkill.name << "] 물리 타격! " << damage << "의 데미지!" << RESET << endl;
                    }
                    else if (selectedSkill.type == 2)
                    {
                        damage = (rand() % 10 + selectedSkill.baseDamage) * 2 + (player.intel * 4);
                        cout << CYAN << "[" << selectedSkill.name << "] 마법 폭발! " << damage << "의 데미지!" << RESET << endl;
                    }
                    else if (selectedSkill.type == 3)
                    {
                        int healAmount = selectedSkill.baseDamage + (player.intel * 2);
                        player.hp += healAmount;
                        if (player.hp > player.maxHp)
                            player.hp = player.maxHp;
                        cout << GREEN << "[" << selectedSkill.name << "] 체력을 " << healAmount << " 회복했습니다!" << RESET << endl;
                    }

                    if (selectedSkill.type != 3)
                    {
                        enemy->takeDamage(damage);
                    }

                    if (enemy->hp > 0)
                    {
                        player.takeDamage((int)(enemy->attack() * statMultiplier));
                    }
                }
                else
                {
                    cout << RED << "마나가 부족합니다! (필요 MP: " << selectedSkill.mpCost << ")" << RESET << endl;
                }
            }
            else
            {
                cout << RED << "잘못된 번호입니다." << RESET << endl;
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

    if (enemy->hp <= 0)
    {
        cout << YELLOW << "\n"
             << enemy->name << "을(를) 물리쳤습니다!" << RESET << endl;

        if (player.activeQuestId == 1 && enemy->name == "초록 고블린")
        {
            player.questProgress++;
            cout << YELLOW << "[퀘스트] 초록 고블린 토벌 진행도: " << player.questProgress << "/3" << RESET << endl;
        }
        else if (player.activeQuestId == 2 && enemy->name == "푸른 슬라임")
        {
            player.questProgress++;
            cout << YELLOW << "[퀘스트] 푸른 슬라임 토벌 진행도: " << player.questProgress << "/5" << RESET << endl;
        }

        int expGain = (int)(((isBoss) ? 200 : 50) * rewardMultiplier);
        player.gainExp(expGain);

        int goldGain = (int)(((rand() % 30 + 10) + (player.dungeonFloor * 2)) * rewardMultiplier);
        player.gold += goldGain;
        cout << YELLOW << goldGain << " 골드를 획득했습니다!" << RESET << endl;

        if (isBoss)
        {
            cout << YELLOW << "보스가 빛나는 전리품을 남겼습니다!" << RESET << endl;
            player.inventory.push_back(Item("슬라임의 왕관", 2, 30, 500));
            cout << GREEN << "가방에 [슬라임의 왕관]이 추가되었습니다!" << RESET << endl;
        }
        else
        {
            int dropRoll = rand() % 100;
            if (dropRoll < 30)
            {
                int itemType = rand() % 3;
                if (itemType == 0)
                {
                    player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                    cout << GREEN << "몬스터가 [체력 포션]을 떨어뜨렸습니다!" << RESET << endl;
                }
                else if (itemType == 1)
                {
                    player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                    cout << CYAN << "몬스터가 [마나 포션]을 떨어뜨렸습니다!" << RESET << endl;
                }
                else
                {
                    player.inventory.push_back(Item("낡은 단검", 1, 3, 10));
                    cout << YELLOW << "몬스터가 [낡은 단검]을 떨어뜨렸습니다!" << RESET << endl;
                }
            }
        }

        player.dungeonFloor++;
        cout << CYAN << "\n더 깊은 곳을 향해 " << player.dungeonFloor << "층으로 나아갑니다!" << RESET << endl;

        if (player.activeQuestId == 3 && player.dungeonFloor >= 5)
        {
            player.questProgress = 1;
            cout << YELLOW << "[퀘스트] 던전 5층 도달 임무 완료! 길드로 돌아가 보상을 받으세요." << RESET << endl;
        }

        cout << "\n엔터를 누르면 마을로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }
}