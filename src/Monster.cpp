#include "../include/Battle.h"
#include "../include/MonsterFactory.h"
#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

void Battle::start(Player &player, int difficulty)
{
    system("cls");
    // 난이도 배율 설정
    float statMultiplier = (difficulty == 1) ? 0.8f : (difficulty == 3) ? 1.5f
                                                                        : 1.0f;
    float rewardMultiplier = (difficulty == 1) ? 0.8f : (difficulty == 3) ? 1.5f
                                                                          : 1.0f;
    string diffName = (difficulty == 1) ? "쉬움" : (difficulty == 3) ? "어려움"
                                                                     : "보통";

    bool isFinalBoss = (player.dungeonFloor == 100);
    bool isBoss = (player.dungeonFloor % 5 == 0) || isFinalBoss;

    // 1. UI 미니맵 렌더링
    cout << CYAN << "\n=== [ 던전 " << player.dungeonFloor << "층 탐색도 (" << diffName << ") ] ===" << RESET << endl;
    int startFloor = ((player.dungeonFloor - 1) / 5) * 5 + 1;
    for (int i = startFloor; i <= startFloor + 4; ++i)
    {
        if (i == player.dungeonFloor)
            cout << GREEN << "[" << i << "F(현재)]" << RESET;
        else if (i % 5 == 0)
            cout << RED << "[BOSS(" << i << "F)]" << RESET;
        else if (i < player.dungeonFloor)
            cout << "\033[90m[CLEAR]\033[0m";
        else
            cout << YELLOW << "[" << i << "F]" << RESET;
        if (i < startFloor + 4)
            cout << " -- ";
    }
    cout << "\n==========================================" << endl;

    // 2. 랜덤 던전 이벤트 (일반 층만)
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

    // 3. 랜덤 던전 환경 설정
    int envType = rand() % 4;
    float envDmgMult = 1.0f;
    if (envType == 1)
        cout << MAGENTA << "[환경] 독안개가 자욱합니다. (매 턴 HP 5 감소)" << RESET << endl;
    else if (envType == 2)
        cout << CYAN << "[환경] 마나의 샘이 흐릅니다. (매 턴 MP 5 회복)" << RESET << endl;
    else if (envType == 3)
    {
        cout << RED << "[환경] 피의 투기장! (모든 데미지 20% 증가)" << RESET << endl;
        envDmgMult = 1.2f;
    }
    else
        cout << "[환경] 고요한 던전 내부입니다." << endl;

    // 4. 몬스터 스폰 및 스탯 보정
    unique_ptr<Monster> enemy(MonsterFactory::spawnMonster(player.dungeonFloor, player.level));
    if (isFinalBoss)
    {
        enemy->name = "마왕";
        enemy->hp = 5000;
        enemy->maxHp = 5000;
    }
    else
    {
        enemy->hp = (int)(enemy->hp * statMultiplier);
        enemy->maxHp = enemy->hp;
    }

    // 난이도 및 투기장 환경을 몬스터의 기본 공격력에 미리 반영
    enemy->atk = (int)(enemy->atk * statMultiplier * envDmgMult);

    cout << "\n지능형 " << RED << enemy->name << RESET << " (이)가 나타났다!" << endl;

    bool inCombat = true;
    int playerStunTurns = 0;
    int playerPoisonTurns = 0;
    int playerBurnTurns = 0;
    int enemyPoisonTurns = 0;
    bool enemyEnraged = false;

    // 5. 전투 루프
    while (inCombat && player.hp > 0 && enemy->hp > 0)
    {
        // 최종 보스 광폭화
        if (isFinalBoss && enemy->hp <= 1500 && !enemyEnraged)
        {
            enemyEnraged = true;
            cout << MAGENTA << "\n========================================" << RESET << endl;
            cout << RED << "[경고] 마왕이 광폭화했습니다! 공격력이 폭증합니다!" << RESET << endl;
            cout << MAGENTA << "========================================\n"
                 << RESET << endl;
            enemy->atk = (int)(enemy->atk * 1.5f);
        }

        cout << "\n------------------------------------------" << endl;
        cout << "[플레이어] HP: " << GREEN << player.hp << "/" << player.maxHp << RESET
             << " | MP: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[" << RED << enemy->name << RESET << "] HP: " << RED << enemy->hp << "/" << enemy->maxHp << RESET << endl;

        // 환경 변수 적용
        if (envType == 1 && rand() % 100 < 50)
        {
            player.hp -= 5;
            cout << MAGENTA << "[독안개] 호흡이 가빠지며 체력이 5 감소했습니다." << RESET << endl;
        }
        else if (envType == 2)
        {
            player.mp += 5;
            if (player.mp > player.maxMp)
                player.mp = player.maxMp;
            cout << CYAN << "[마나 샘] 마나가 5 회복되었습니다." << RESET << endl;
        }

        // 플레이어 상태 이상 처리
        if (playerPoisonTurns > 0)
        {
            int pDmg = 10 + player.dungeonFloor;
            player.hp -= pDmg;
            cout << MAGENTA << "독에 중독되어 " << pDmg << "의 피해! (남은 턴: " << playerPoisonTurns << ")" << RESET << endl;
            playerPoisonTurns--;
        }
        if (playerBurnTurns > 0)
        {
            int bDmg = 15 + (player.dungeonFloor * 2);
            player.hp -= bDmg;
            cout << RED << "화상으로 인해 " << bDmg << "의 피해! (남은 턴: " << playerBurnTurns << ")" << RESET << endl;
            playerBurnTurns--;
        }
        if (player.hp <= 0)
        {
            cout << RED << "지속 피해로 쓰러졌습니다..." << RESET << endl;
            break;
        }

        // 플레이어 턴
        if (playerStunTurns > 0)
        {
            cout << RED << "기절 상태입니다! 이번 턴은 행동할 수 없습니다." << RESET << endl;
            playerStunTurns--;
        }
        else
        {
            cout << "1. 기본 공격  2. 스킬북  3. 가방  4. 도망\n선택: ";
            int combatChoice;
            cin >> combatChoice;
            system("cls");

            switch (combatChoice)
            {
            case 1:
            { // 기본 공격
                if (rand() % 100 < 10)
                    cout << YELLOW << "공격이 빗나갔습니다!" << RESET << endl;
                else
                {
                    if (player.weaponDurability > 0)
                        player.weaponDurability--;
                    int damage = player.attack(); // 소켓 보석 효과 포함됨
                    if (player.weaponDurability <= 0)
                    {
                        damage -= player.weaponDamage;
                        if (damage < 1)
                            damage = 1;
                    }

                    int critChance = (player.jobClass == 3) ? 30 : 15;
                    float critMult = (player.jobClass == 3) ? 2.0f : 1.5f;
                    if (rand() % 100 < critChance)
                    {
                        damage = (int)(damage * critMult);
                        cout << RED << "크리티컬!" << RESET << endl;
                    }

                    damage = (int)(damage * envDmgMult); // 투기장 증폭
                    enemy->takeDamage(damage);
                    cout << YELLOW << damage << "의 피해를 입혔습니다!" << RESET << endl;
                }
                break;
            }
            case 2:
            { // 스킬
                if (player.skills.empty())
                {
                    cout << RED << "배운 스킬이 없습니다!" << RESET << endl;
                    continue;
                }
                cout << "\n=== 스킬북 ===" << endl;
                for (size_t i = 0; i < player.skills.size(); ++i)
                    cout << i + 1 << ". " << player.skills[i].name << " (MP: " << player.skills[i].mpCost << ")" << endl;
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
                            damage = (int)(damage * envDmgMult);
                            cout << YELLOW << "[" << s.name << "] 타격! " << damage << " 피해!" << RESET << endl;
                        }
                        else if (s.type == 2)
                        {
                            damage = (rand() % 10 + s.baseDamage) * 2 + (player.intel * 4);
                            damage = (int)(damage * envDmgMult);
                            cout << CYAN << "[" << s.name << "] 폭발! " << damage << " 피해!" << RESET << endl;
                            if (player.jobClass == 2)
                            { // 마법사 마나 흡혈
                                int healAmount = s.mpCost / 2;
                                player.hp = min(player.maxHp, player.hp + healAmount);
                                cout << MAGENTA << "[마법사] 마나 흡혈! 체력 +" << healAmount << RESET << endl;
                            }
                        }
                        else if (s.type == 3)
                        {
                            int heal = s.baseDamage + (player.intel * 2);
                            player.hp = min(player.maxHp, player.hp + heal);
                            cout << GREEN << "체력 +" << heal << " 회복!" << RESET << endl;
                        }
                        if (s.type != 3)
                            enemy->takeDamage(damage);
                        if (s.name == "독 찌르기")
                        {
                            enemyPoisonTurns = 3;
                            cout << MAGENTA << enemy->name << " 중독! (3턴)" << RESET << endl;
                        }
                    }
                    else
                    {
                        cout << RED << "마나가 부족합니다!" << RESET << endl;
                        continue;
                    }
                }
                else
                    continue;
                break;
            }
            case 3:
            { // 가방
                player.openInventory();
                continue; // 아이템 사용 후 다시 선택
            }
            case 4:
            { // 도망
                if (isBoss)
                {
                    cout << RED << "보스전에서는 도망칠 수 없습니다!" << RESET << endl;
                    continue;
                }
                int penalty = player.gold / 10;
                player.gold -= penalty;
                cout << "도망쳤습니다... (-" << penalty << " G)" << endl;
                inCombat = false;
                continue;
            }
            default:
                cout << RED << "잘못된 입력입니다." << RESET << endl;
                continue;
            }
        }

        // 몬스터 턴 (지능형 AI 작동)
        if (enemy->hp > 0 && inCombat)
        {
            if (rand() % 100 < 10)
                cout << GREEN << "회피 성공! 적의 공격을 피했습니다." << RESET << endl;
            else
            {
                cout << "\n--- " << enemy->name << "의 턴 ---" << endl;
                enemy->takeAction(player); // 몬스터가 상황에 맞게 스킬/공격/회복을 결정함

                // 기존 상태 이상 부여 확률 유지 (기본 공격 외에도 발생 가능하도록)
                if (rand() % 100 < 15)
                {
                    cout << MAGENTA << enemy->name << "의 맹독 공격! 중독되었습니다." << RESET << endl;
                    playerPoisonTurns += 3;
                }
                else if (rand() % 100 < 25)
                {
                    cout << RED << enemy->name << "의 화염 공격! 화상." << RESET << endl;
                    playerBurnTurns += 2;
                }
                if (isBoss && rand() % 100 < 20)
                {
                    cout << RED << enemy->name << "의 강력한 일격! 기절!" << RESET << endl;
                    playerStunTurns = 1;
                }
            }
        }

        // 펫 개입 로직
        if (inCombat && enemy->hp > 0 && player.hp > 0)
        {
            if (player.activePet == 1)
            {
                int petDmg = (int)((15 + (player.level * 2)) * envDmgMult);
                enemy->hp -= petDmg;
                cout << YELLOW << "[동행 펫] 전투 늑대가 적을 물어뜯어 " << petDmg << "의 피해!" << RESET << endl;
            }
            else if (player.activePet == 2)
            {
                int petHeal = 10 + player.level;
                player.hp = min(player.maxHp, player.hp + petHeal);
                cout << GREEN << "[동행 펫] 치유의 요정이 체력을 " << petHeal << " 회복시켰습니다!" << RESET << endl;
            }
        }

        // 적 독 데미지
        if (enemyPoisonTurns > 0 && enemy->hp > 0 && inCombat)
        {
            int poisonDmg = 15;
            enemy->hp -= poisonDmg;
            cout << MAGENTA << enemy->name << " 독 피해 " << poisonDmg << "! (남은 턴: " << enemyPoisonTurns - 1 << ")" << RESET << endl;
            enemyPoisonTurns--;
        }
    }

    // 전투 종료 처리
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
            cout << "\n마침내 마왕을 물리치고 세계에 평화를 가져왔습니다!" << endl;
            cout << "\n엔터를 누르면 게임이 종료됩니다...";
            cin.ignore();
            cin.get();
            exit(0);
        }

        // 퀘스트 진행도
        if (player.activeQuestId == 1 && enemy->name == "초록 고블린")
            player.questProgress++;
        else if (player.activeQuestId == 2 && enemy->name == "푸른 슬라임")
            player.questProgress++;

        player.gainExp((int)(((isBoss) ? 200 : 50) * rewardMultiplier));
        int goldGain = (int)(((rand() % 30 + 10) + (player.dungeonFloor * 2)) * rewardMultiplier);
        player.gold += goldGain;
        cout << YELLOW << goldGain << " 골드 획득!" << RESET << endl;

        // 은행 복리 이자 스노우볼
        if (player.bankGold > 0)
        {
            int interest = player.bankGold * 3 / 100;
            player.bankGold += interest;
            cout << CYAN << "은행 예금에 3% 복리 이자가 붙었습니다! (+" << interest << "G)" << RESET << endl;
        }

        player.totalKills++;
        player.checkAchievements();

        // 아이템 드랍
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
            if (rand() % 100 < 40)
            {
                int type = rand() % 3;
                if (type == 0)
                {
                    player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                    cout << GREEN << "[체력 포션] 획득!" << RESET << endl;
                }
                else if (type == 1)
                {
                    player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                    cout << CYAN << "[마나 포션] 획득!" << RESET << endl;
                }
                else
                {
                    player.inventory.push_back(Item("가죽 갑옷", 2, 10, 80));
                    cout << MAGENTA << "[가죽 갑옷] 획득!" << RESET << endl;
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