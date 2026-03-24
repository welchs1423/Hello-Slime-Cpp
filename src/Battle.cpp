#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include "../include/InputHelpers.h"
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

    bool isFinalBoss = (player.dungeonFloor == 100);
    bool isBoss = (player.dungeonFloor % 5 == 0) || isFinalBoss;

    cout << "\n=== 던전 " << player.dungeonFloor << "층 [" << diffName << "] ===" << endl;

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

    std::unique_ptr<Monster> enemy(MonsterFactory::spawnMonster(player.dungeonFloor, player.level));

    if (isFinalBoss)
    {
        enemy->name = "마왕 (최종 보스)";
        enemy->hp = 5000;
    }
    else
    {
        enemy->hp = (int)(enemy->hp * statMultiplier);
    }

    cout << "야생의 " << RED << enemy->name << RESET << " (이)가 나타났다! (HP: " << RED << enemy->hp << RESET << ")" << endl;

    bool inCombat = true;
    int enemyPoisonTurns = 0;
    int playerStunTurns = 0;

    while (inCombat && player.hp > 0 && enemy->hp > 0)
    {
        cout << "\n[플레이어] 체력: " << GREEN << player.hp << "/" << player.maxHp << RESET
             << " | 마나: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << YELLOW << "[장비 내구도] 무기: " << player.weaponDurability << " | 방어구: " << player.armorDurability << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] 체력: " << RED << enemy->hp << RESET << endl;

        if (playerStunTurns > 0)
        {
            cout << RED << "기절 상태입니다! 이번 턴은 행동할 수 없습니다." << RESET << endl;
            playerStunTurns--;
        }
        else
        {
            cout << "1. 기본 공격  2. 스킬북 펼치기  3. 가방 열기  4. 도망가기\n선택: ";

            int combatChoice = readIntInRange(1, 4);
            system("cls");

            switch (combatChoice)
            {
            case 1:
            {
                int hitRoll = rand() % 100;
                if (hitRoll < 10)
                {
                    cout << YELLOW << "공격이 빗나갔습니다! " << enemy->name << "이(가) 회피했습니다." << RESET << endl;
                }
                else
                {
                    if (player.weaponDurability > 0)
                        player.weaponDurability--;

                    int damage = player.attack();
                    if (player.weaponDurability <= 0)
                    {
                        damage -= player.weaponDamage;
                        if (damage < 1)
                            damage = 1;
                        cout << RED << "경고: 무기 내구도가 0입니다! 무기 공격력이 무효화됩니다." << RESET << endl;
                    }

                    int critRoll = rand() % 100;
                    if (critRoll < 15)
                    {
                        damage = (int)(damage * 1.5);
                        cout << RED << "크리티컬 적중! 치명적인 피해를 입혔습니다!" << RESET << endl;
                    }
                    enemy->takeDamage(damage);
                }
                break;
            }
            case 2:
            {
                if (player.skills.empty())
                {
                    cout << RED << "배운 스킬이 없습니다!" << RESET << endl;
                    continue;
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

                int skillChoice = readIntInRange(0, static_cast<int>(player.skills.size()));

                if (skillChoice == 0)
                    continue;

                if (skillChoice > 0 && skillChoice <= player.skills.size())
                {
                    Skill &selectedSkill = player.skills[skillChoice - 1];

                    if (player.mp >= selectedSkill.mpCost)
                    {
                        player.mp -= selectedSkill.mpCost;

                        int damage = 0;
                        if (selectedSkill.type == 1)
                        {
                            if (player.weaponDurability > 0)
                                player.weaponDurability--;
                            damage = (rand() % 10 + selectedSkill.baseDamage + player.weaponDamage + (player.weaponLevel * 5)) + (player.str * 3);
                            if (player.weaponDurability <= 0)
                            {
                                damage -= player.weaponDamage;
                                cout << RED << "경고: 무기 내구도가 0입니다! 물리 스킬 위력이 반감됩니다." << RESET << endl;
                            }
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

                        if (selectedSkill.name == "독 찌르기")
                        {
                            enemyPoisonTurns = 3;
                            cout << MAGENTA << enemy->name << "이(가) 독에 중독되었습니다! (3턴)" << RESET << endl;
                        }
                    }
                    else
                    {
                        cout << RED << "마나가 부족합니다! (필요 MP: " << selectedSkill.mpCost << ")" << RESET << endl;
                        continue;
                    }
                }
                else
                {
                    cout << RED << "잘못된 번호입니다." << RESET << endl;
                    continue;
                }
                break;
            }
            case 3:
                player.openInventory();
                continue;
            case 4:
            {
                if (isBoss)
                {
                    cout << RED << "보스전에서는 도망칠 수 없습니다!" << RESET << endl;
                    continue;
                }

                int penaltyGold = player.gold / 10;
                player.gold -= penaltyGold;

                cout << "겁에 질려 마을로 도망쳤습니다... (페널티: " << penaltyGold << " 골드 상실)" << endl;
                inCombat = false;
                continue;
            }
            default:
                cout << RED << "잘못된 입력입니다." << RESET << endl;
                continue;
            }
        }

        if (enemy->hp > 0 && inCombat)
        {
            player.tryAutoHeal();

            int dodgeRoll = rand() % 100;
            if (dodgeRoll < 10)
            {
                cout << GREEN << "회피 성공! 적의 공격을 날렵하게 피했습니다." << RESET << endl;
            }
            else
            {
                int enemyDmg = isFinalBoss ? 150 : (int)(enemy->attack() * statMultiplier);

                int enemyCrit = rand() % 100;
                if (enemyCrit < 15)
                {
                    enemyDmg = (int)(enemyDmg * 1.5);
                    cout << RED << "치명타를 허용했습니다! 강력한 피해를 입었습니다." << RESET << endl;
                }

                if (player.armorDurability > 0)
                    player.armorDurability--;
                if (player.armorDurability <= 0)
                {
                    enemyDmg += player.armorDefense;
                    cout << RED << "경고: 방어구 내구도가 0입니다! 추가 피해를 입습니다." << RESET << endl;
                }

                player.takeDamage(enemyDmg);

                if (isBoss && rand() % 100 < 20)
                {
                    cout << RED << enemy->name << "의 강력한 일격! 플레이어가 기절했습니다!" << RESET << endl;
                    playerStunTurns = 1;
                }
            }
        }

        if (enemyPoisonTurns > 0 && enemy->hp > 0 && inCombat)
        {
            int poisonDmg = 15;
            enemy->hp -= poisonDmg;
            cout << MAGENTA << enemy->name << "이(가) 독 피해를 " << poisonDmg << " 입었습니다. (남은 턴: " << enemyPoisonTurns - 1 << ")" << RESET << endl;
            enemyPoisonTurns--;
        }
    }

    if (enemy->hp <= 0)
    {
        cout << YELLOW << "\n"
             << enemy->name << "을(를) 물리쳤습니다!" << RESET << endl;

        if (isFinalBoss)
        {
            cout << "\n========================================" << endl;
            cout << "                ENDING                  " << endl;
            cout << "========================================" << endl;
            cout << "마침내 마왕을 물리치고 세계에 평화를 가져왔습니다!" << endl;
            cout << "당신의 전설은 영원히 기억될 것입니다." << endl;
            cout << "플레이해주셔서 감사합니다." << endl;
            cout << "========================================" << endl;
            cout << "\n엔터를 누르면 게임이 종료됩니다...";
            cin.ignore();
            cin.get();
            exit(0);
        }

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

        player.totalKills++;
        player.checkAchievements();

        if (isBoss)
        {
            cout << YELLOW << "보스가 빛나는 전리품을 남겼습니다!" << RESET << endl;
            if (rand() % 100 < 5)
            {
                player.inventory.push_back(Item("전설의 엑스칼리버", 1, 100, 2000));
                cout << MAGENTA << "!!! 전설 등급 아이템 [전설의 엑스칼리버]를 획득했습니다 !!!" << RESET << endl;
            }
            else
            {
                player.inventory.push_back(Item("슬라임의 왕관", 2, 30, 500));
                cout << GREEN << "가방에 [슬라임의 왕관]이 추가되었습니다!" << RESET << endl;
            }
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

        cout << "\n전투 결과를 자동 저장합니다..." << endl;
        player.save();

        cout << "\n엔터를 누르면 마을로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }
}