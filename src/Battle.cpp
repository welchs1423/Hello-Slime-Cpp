#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>

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
        if (DungeonEvent::triggerEvent(player))
        {
            player.dungeonFloor++;
            return;
        }
        if (player.hp <= 0)
            return;
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
    int playerPoisonTurns = 0;
    int playerBurnTurns = 0;
    bool enemyEnraged = false;

    while (inCombat && player.hp > 0 && enemy->hp > 0)
    {
        if (isFinalBoss && enemy->hp <= 1500 && !enemyEnraged)
        {
            enemyEnraged = true;
            cout << MAGENTA << "\n========================================" << RESET << endl;
            cout << RED << "[경고] 마왕이 광폭화(Enrage) 상태에 돌입합니다!" << RESET << endl;
            cout << YELLOW << "마왕: 크아아악! 네놈 따위에게... 진정한 공포를 보여주마!!!" << RESET << endl;
            cout << MAGENTA << "========================================\n"
                 << RESET << endl;
            statMultiplier *= 1.5f;
        }

        cout << "\n[플레이어] 체력: " << GREEN << player.hp << "/" << player.maxHp << RESET << " | 마나: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << YELLOW << "[장비 내구도] 무기: " << player.weaponDurability << " | 방어구: " << player.armorDurability << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] 체력: " << RED << enemy->hp << RESET << endl;

        if (playerPoisonTurns > 0)
        {
            int pDmg = 10 + player.dungeonFloor;
            player.hp -= pDmg;
            cout << MAGENTA << "독에 중독되어 " << pDmg << "의 피해를 입었습니다! (남은 턴: " << playerPoisonTurns << ")" << RESET << endl;
            playerPoisonTurns--;
        }
        if (playerBurnTurns > 0)
        {
            int bDmg = 15 + (player.dungeonFloor * 2);
            player.hp -= bDmg;
            cout << RED << "화상으로 인해 " << bDmg << "의 피해를 입었습니다! (남은 턴: " << playerBurnTurns << ")" << RESET << endl;
            playerBurnTurns--;
        }
        if (player.hp <= 0)
        {
            cout << RED << "상태 이상 피해로 쓰러졌습니다..." << RESET << endl;
            break;
        }

        if (playerStunTurns > 0)
        {
            cout << RED << "기절 상태입니다! 이번 턴은 행동할 수 없습니다." << RESET << endl;
            playerStunTurns--;
        }
        else
        {
            cout << "1. 기본 공격  2. 스킬북 펼치기  3. 가방 (아이템 사용)  4. 도망가기\n선택: ";
            int combatChoice;
            cin >> combatChoice;
            system("cls");

            switch (combatChoice)
            {
            case 1:
            {
                if (rand() % 100 < 10)
                    cout << YELLOW << "공격이 빗나갔습니다! 회피당했습니다." << RESET << endl;
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
                        cout << RED << "무기 내구도가 0입니다! 공격력이 무효화됩니다." << RESET << endl;
                    }

                    int critChance = (player.jobClass == 3) ? 30 : 15;
                    float critMult = (player.jobClass == 3) ? 2.0f : 1.5f;

                    if (rand() % 100 < critChance)
                    {
                        damage = (int)(damage * critMult);
                        cout << RED << "크리티컬! 치명적인 피해를 입혔습니다!" << RESET << endl;
                        if (player.jobClass == 3)
                            cout << MAGENTA << "[도적 패시브] 암살 발동! 치명타 피해가 증폭됩니다." << RESET << endl;
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
                    cout << i + 1 << ". [" << player.skills[i].getTypeName() << "] " << player.skills[i].name << " (MP: " << player.skills[i].mpCost << ")" << endl;
                cout << "0. 취소\n선택: ";
                int skillChoice;
                cin >> skillChoice;
                if (skillChoice == 0)
                    continue;
                if (skillChoice > 0 && skillChoice <= player.skills.size())
                {
                    Skill &s = player.skills[skillChoice - 1];
                    if (player.mp >= s.mpCost)
                    {
                        player.mp -= s.mpCost;
                        int damage = 0;
                        if (s.type == 1)
                        {
                            if (player.weaponDurability > 0)
                                player.weaponDurability--;
                            damage = (rand() % 10 + s.baseDamage + player.weaponDamage + (player.weaponLevel * 5)) + (player.str * 3);
                            if (player.weaponDurability <= 0)
                                damage -= player.weaponDamage;
                            cout << YELLOW << "[" << s.name << "] 물리 타격! " << damage << " 피해!" << RESET << endl;
                        }
                        else if (s.type == 2)
                        {
                            damage = (rand() % 10 + s.baseDamage) * 2 + (player.intel * 4);
                            cout << CYAN << "[" << s.name << "] 마법 폭발! " << damage << " 피해!" << RESET << endl;
                            if (player.jobClass == 2)
                            {
                                int healAmount = s.mpCost / 2;
                                player.hp += healAmount;
                                if (player.hp > player.maxHp)
                                    player.hp = player.maxHp;
                                cout << MAGENTA << "[마법사 패시브] 마나 흡혈! 체력을 " << healAmount << " 회복했습니다." << RESET << endl;
                            }
                        }
                        else if (s.type == 3)
                        {
                            int heal = s.baseDamage + (player.intel * 2);
                            player.hp += heal;
                            if (player.hp > player.maxHp)
                                player.hp = player.maxHp;
                            cout << GREEN << "체력을 " << heal << " 회복했습니다!" << RESET << endl;
                        }

                        if (s.type != 3)
                            enemy->takeDamage(damage);
                        if (s.name == "독 찌르기")
                        {
                            enemyPoisonTurns = 3;
                            cout << MAGENTA << enemy->name << "이(가) 독에 중독되었습니다! (3턴)" << RESET << endl;
                        }
                    }
                    else
                    {
                        cout << RED << "마나가 부족합니다!" << RESET << endl;
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
            {
                if (player.inventory.empty())
                {
                    cout << RED << "가방이 비어있습니다." << RESET << endl;
                    continue;
                }
                cout << YELLOW << "\n=== 가방 (아이템 사용) ===" << RESET << endl;
                for (size_t i = 0; i < player.inventory.size(); ++i)
                    cout << i + 1 << ". [" << player.inventory[i].getTypeName() << "] " << player.inventory[i].name << " (효과: " << player.inventory[i].effectValue << ")" << endl;
                cout << "0. 취소\n선택: ";
                int itemChoice;
                cin >> itemChoice;
                if (itemChoice == 0)
                    continue;
                if (itemChoice > 0 && itemChoice <= player.inventory.size())
                {
                    int index = itemChoice - 1;
                    Item &item = player.inventory[index];
                    if (item.type == 3)
                    {
                        player.hp += item.effectValue;
                        if (player.hp > player.maxHp)
                            player.hp = player.maxHp;
                        cout << GREEN << item.name << " 사용! 체력 회복." << RESET << endl;
                        if (player.potions > 0)
                            player.potions--;
                        player.inventory.erase(player.inventory.begin() + index);
                    }
                    else if (item.type == 4)
                    {
                        player.mp += item.effectValue;
                        if (player.mp > player.maxMp)
                            player.mp = player.maxMp;
                        cout << CYAN << item.name << " 사용! 마나 회복." << RESET << endl;
                        if (player.manaPotions > 0)
                            player.manaPotions--;
                        player.inventory.erase(player.inventory.begin() + index);
                    }
                    else if (item.type == 5)
                    {
                        playerPoisonTurns = 0;
                        playerBurnTurns = 0;
                        playerStunTurns = 0;
                        cout << YELLOW << item.name << " 사용! 모든 상태 이상이 치료되었습니다." << RESET << endl;
                        player.inventory.erase(player.inventory.begin() + index);
                    }
                    else
                    {
                        cout << RED << "전투 중 사용할 수 없는 아이템입니다." << RESET << endl;
                        continue;
                    }
                }
                else
                    continue;
                break;
            }
            case 4:
            {
                if (isBoss)
                {
                    cout << RED << "보스전에서는 도망칠 수 없습니다!" << RESET << endl;
                    continue;
                }
                int penalty = player.gold / 10;
                player.gold -= penalty;
                cout << "도망쳤습니다... (페널티: " << penalty << " 골드 상실)" << endl;
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
            if (rand() % 100 < 10)
                cout << GREEN << "회피 성공! 적의 공격을 피했습니다." << RESET << endl;
            else
            {
                int enemyDmg = isFinalBoss ? 150 : (int)(enemy->attack() * statMultiplier);

                if (player.jobClass == 1 && rand() % 100 < 15)
                {
                    cout << MAGENTA << "[전사 패시브] 방패 막기! 적의 공격을 완벽히 방어했습니다." << RESET << endl;
                    enemyDmg = 0;
                }
                else
                {
                    if (rand() % 100 < 15)
                    {
                        enemyDmg = (int)(enemyDmg * 1.5);
                        cout << RED << "치명타를 허용했습니다!" << RESET << endl;
                    }
                    if (player.armorDurability > 0)
                        player.armorDurability--;
                    if (player.armorDurability <= 0)
                    {
                        enemyDmg += player.armorDefense;
                        cout << RED << "방어구 내구도가 0입니다! 추가 피해를 입습니다." << RESET << endl;
                    }

                    int statusRoll = rand() % 100;
                    if (statusRoll < 15)
                    {
                        cout << MAGENTA << enemy->name << "의 맹독 공격! 독에 감염되었습니다." << RESET << endl;
                        playerPoisonTurns += 3;
                    }
                    else if (statusRoll < 25)
                    {
                        cout << RED << enemy->name << "의 화염 공격! 몸에 불이 붙었습니다." << RESET << endl;
                        playerBurnTurns += 2;
                    }
                }

                player.takeDamage(enemyDmg);
                if (isBoss && rand() % 100 < 20 && enemyDmg > 0)
                {
                    cout << RED << enemy->name << "의 강력한 일격! 기절했습니다!" << RESET << endl;
                    playerStunTurns = 1;
                }
            }
        }

        // 펫 자동 개입 로직 (매 턴 끝마다 발동)
        if (inCombat && enemy->hp > 0 && player.hp > 0)
        {
            if (player.activePet == 1)
            {
                int petDmg = 15 + (player.level * 2);
                enemy->hp -= petDmg;
                cout << YELLOW << "[동행 펫] 전투 늑대가 " << enemy->name << "을(를) 물어뜯어 " << petDmg << "의 피해를 입혔습니다!" << RESET << endl;
            }
            else if (player.activePet == 2)
            {
                int petHeal = 10 + player.level;
                player.hp += petHeal;
                if (player.hp > player.maxHp)
                    player.hp = player.maxHp;
                cout << GREEN << "[동행 펫] 치유의 요정이 마법을 걸어 체력을 " << petHeal << " 회복시켰습니다!" << RESET << endl;
            }
        }

        if (enemyPoisonTurns > 0 && enemy->hp > 0 && inCombat)
        {
            int poisonDmg = 15;
            enemy->hp -= poisonDmg;
            cout << MAGENTA << enemy->name << "이(가) 독 피해 " << poisonDmg << "을 입었습니다. (남은 턴: " << enemyPoisonTurns - 1 << ")" << RESET << endl;
            enemyPoisonTurns--;
        }
    }

    if (enemy->hp <= 0)
    {
        cout << YELLOW << "\n"
             << enemy->name << "을(를) 물리쳤습니다!" << RESET << endl;
        if (isFinalBoss)
        {
            cout << YELLOW << R"(
  __  __   _   ___ _____ ___ ___  
 |  \/  | /_\ / __|_   _| __| _ \ 
 | |\/| |/ _ \\__ \ | | | _||   / 
 |_|  |_/_/ \_\___/ |_| |___|_|_\ 
            )" << RESET
                 << endl;
            cout << "\n========================================" << endl;
            cout << "마침내 마왕을 물리치고 세계에 평화를 가져왔습니다!" << endl;
            cout << "당신의 전설은 영원히 기억될 것입니다." << endl;
            cout << "플레이해주셔서 감사합니다." << endl;
            cout << "========================================" << endl;
            cout << "\n엔터를 누르면 게임이 완전히 종료됩니다...";
            cin.ignore();
            cin.get();
            exit(0);
        }
        if (player.activeQuestId == 1 && enemy->name == "초록 고블린")
            player.questProgress++;
        else if (player.activeQuestId == 2 && enemy->name == "푸른 슬라임")
            player.questProgress++;

        player.gainExp((int)(((isBoss) ? 200 : 50) * rewardMultiplier));
        int goldGain = (int)(((rand() % 30 + 10) + (player.dungeonFloor * 2)) * rewardMultiplier);
        player.gold += goldGain;
        cout << YELLOW << goldGain << " 골드 획득!" << RESET << endl;

        player.totalKills++;
        player.checkAchievements();

        if (isBoss)
        {
            if (rand() % 100 < 5)
            {
                player.inventory.push_back(Item("전설의 엑스칼리버", 1, 100, 2000));
                cout << MAGENTA << "!!! 전설 무기 [전설의 엑스칼리버] 획득 !!!" << RESET << endl;
            }
            else
            {
                player.inventory.push_back(Item("슬라임의 왕관", 2, 30, 500));
                cout << GREEN << "[슬라임의 왕관] 획득!" << RESET << endl;
            }
        }
        else
        {
            int dropRoll = rand() % 100;
            if (dropRoll < 40)
            {
                int type = rand() % 5;
                if (type == 0)
                {
                    player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                    cout << GREEN << "몬스터가 [체력 포션]을 떨어뜨렸습니다!" << RESET << endl;
                }
                else if (type == 1)
                {
                    player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                    cout << CYAN << "몬스터가 [마나 포션]을 떨어뜨렸습니다!" << RESET << endl;
                }
                else if (type == 2)
                {
                    player.inventory.push_back(Item("만병통치약", 5, 0, 50));
                    cout << YELLOW << "몬스터가 [만병통치약]을 떨어뜨렸습니다!" << RESET << endl;
                }
                else
                {
                    int prefixRoll = rand() % 100;
                    string prefix = "";
                    int bonus = 0;
                    int priceBonus = 0;
                    if (prefixRoll < 10)
                    {
                        prefix = "전설의 ";
                        bonus = 20;
                        priceBonus = 300;
                    }
                    else if (prefixRoll < 30)
                    {
                        prefix = "불타는 ";
                        bonus = 10;
                        priceBonus = 150;
                    }
                    else if (prefixRoll < 60)
                    {
                        prefix = "날카로운 ";
                        bonus = 5;
                        priceBonus = 50;
                    }

                    if (type == 3)
                    {
                        player.inventory.push_back(Item(prefix + "강철 검", 1, 15 + bonus, 100 + priceBonus));
                        cout << MAGENTA << "몬스터가 [" << prefix << "강철 검]을 떨어뜨렸습니다!" << RESET << endl;
                    }
                    else
                    {
                        player.inventory.push_back(Item(prefix + "가죽 갑옷", 2, 10 + bonus, 80 + priceBonus));
                        cout << MAGENTA << "몬스터가 [" << prefix << "가죽 갑옷]을 떨어뜨렸습니다!" << RESET << endl;
                    }
                }
            }
        }
        player.dungeonFloor++;
        cout << CYAN << "\n"
             << player.dungeonFloor << "층으로 나아갑니다!" << RESET << endl;
        player.save();
        cout << "\n엔터를 누르면 마을로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }
}