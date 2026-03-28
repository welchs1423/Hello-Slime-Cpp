#include "../include/Raid.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Raid::visit(Player &player)
{
    system("cls");
    cout << RED << "\n=== [ 월드 보스 레이드: 고대 파멸의 드래곤 ] ===" << RESET << endl;
    cout << "경비대장: 저 끔찍한 괴물은 죽일 수 없습니다! 최대한 시선을 끌고 상처를 입혀주십시오!" << endl;
    cout << "경비대장: 입힌 피해량(DPS)에 따라 왕국에서 막대한 포상금을 지급할 것입니다!" << endl;

    cout << "\n1. 드래곤의 둥지로 진입한다  2. 아직 준비가 안 됐다\n선택: ";
    int choice;
    cin >> choice;
    if (choice != 1)
        return;

    system("cls");
    cout << MAGENTA << "\n==============================================" << RESET << endl;
    cout << RED << " 크롸아아아아!! 고대 파멸의 드래곤이 포효합니다!" << RESET << endl;
    cout << MAGENTA << "==============================================\n"
         << RESET << endl;

    int bossMaxHp = 999999;
    int bossHp = bossMaxHp;
    int bossBaseAtk = 50 + (player.level * 5); // 플레이어 레벨에 비례하여 시작

    int turn = 1;
    int totalDamageDealt = 0;
    bool inRaid = true;

    while (inRaid && player.hp > 0 && bossHp > 0)
    {
        cout << "\n--- [ 레이드 턴 : " << turn << " ] ---" << endl;
        cout << "[플레이어] HP: " << GREEN << player.hp << "/" << player.maxHp << RESET
             << " | MP: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
        cout << "[파멸의 드래곤] HP: " << RED << bossHp << " / " << bossMaxHp << RESET << endl;
        cout << YELLOW << "(현재까지 누적 딜량: " << totalDamageDealt << ")" << RESET << endl;

        cout << "\n1. 기본 공격  2. 스킬 사용  3. 가방 열기  4. 포기하고 도망\n선택: ";
        int bChoice;
        cin >> bChoice;
        system("cls");

        int turnDamage = 0;

        if (bChoice == 1)
        {
            turnDamage = player.attack();
            if (rand() % 100 < 20)
            {
                turnDamage = (int)(turnDamage * 1.5);
                cout << YELLOW << "크리티컬!" << RESET << endl;
            }
        }
        else if (bChoice == 2)
        {
            if (player.skills.empty())
            {
                cout << RED << "배운 스킬이 없습니다!" << RESET << endl;
                continue;
            }
            cout << "\n=== 스킬북 ===" << endl;
            for (size_t i = 0; i < player.skills.size(); ++i)
                cout << i + 1 << ". " << player.skills[i].name << " (MP: " << player.skills[i].mpCost << ")" << endl;
            cout << "0. 취소\n선택: ";
            int sChoice;
            cin >> sChoice;
            if (sChoice > 0 && sChoice <= player.skills.size())
            {
                Skill &s = player.skills[sChoice - 1];
                if (player.mp >= s.mpCost)
                {
                    player.mp -= s.mpCost;
                    if (s.type == 1 || s.type == 2)
                    { // 공격형 스킬
                        turnDamage = (s.baseDamage * 2) + (player.str * 3) + (player.intel * 3) + player.weaponDamage;
                        cout << CYAN << "[" << s.name << "] 작렬!" << RESET << endl;
                    }
                    else if (s.type == 3)
                    { // 회복
                        int heal = s.baseDamage + (player.intel * 2);
                        player.hp = min(player.maxHp, player.hp + heal);
                        cout << GREEN << "체력 " << heal << " 회복!" << RESET << endl;
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
        }
        else if (bChoice == 3)
        {
            player.openInventory();
            continue;
        }
        else if (bChoice == 4)
        {
            cout << "드래곤의 위압감에 눌려 황급히 도망칩니다!" << endl;
            inRaid = false;
        }
        else
        {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 딜량 적용
        if (turnDamage > 0)
        {
            bossHp -= turnDamage;
            totalDamageDealt += turnDamage;
            cout << YELLOW << "드래곤에게 " << turnDamage << "의 피해를 입혔습니다!" << RESET << endl;
        }

        // 보스의 턴 (턴이 지날수록 광폭화)
        if (inRaid && bossHp > 0)
        {
            int currentBossAtk = bossBaseAtk + (turn * 10); // 매 턴마다 공격력이 10씩 강해짐
            cout << "\n--- 드래곤의 반격 ---" << endl;

            if (turn % 3 == 0)
            { // 3턴마다 브레스
                cout << MAGENTA << "드래곤이 숨을 들이마신 후 파멸의 브레스를 뿜어냅니다!!!" << RESET << endl;
                player.takeDamage(currentBossAtk * 2);
            }
            else
            {
                cout << RED << "드래곤이 거대한 발톱으로 내려칩니다!" << RESET << endl;
                player.takeDamage(currentBossAtk);
            }
            turn++;
        }
    }

    // 레이드 종료 및 정산
    cout << "\n==============================================" << endl;
    if (player.hp <= 0)
    {
        cout << RED << "드래곤의 압도적인 힘에 쓰러졌습니다..." << RESET << endl;
        cout << "경비대원들이 당신을 구출하여 마을로 데려왔습니다." << endl;
        player.hp = 1; // 죽음 페널티 방지
    }

    int rewardGold = totalDamageDealt / 2; // 딜량 2당 1골드
    int rewardExp = totalDamageDealt / 5;  // 딜량 5당 1경험치

    cout << YELLOW << "\n[ 레이드 정산 ]" << RESET << endl;
    cout << "총 입힌 피해량: " << MAGENTA << totalDamageDealt << RESET << endl;
    cout << "획득 포상금: " << YELLOW << rewardGold << " G" << RESET << endl;
    cout << "획득 경험치: " << CYAN << rewardExp << " EXP" << RESET << endl;

    player.gold += rewardGold;
    player.gainExp(rewardExp);

    cout << "\n엔터를 누르면 마을 광장으로 돌아갑니다...";
    cin.ignore();
    cin.get();
}