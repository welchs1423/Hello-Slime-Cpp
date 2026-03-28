#include "../include/Abyss.h"
#include "../include/MonsterFactory.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>

using namespace std;

void Abyss::visit(Player &player)
{
    system("cls");
    cout << MAGENTA << R"(
       _   _                    _____       _       
      /_\ | |__ _  _ ____ ___  / ____| __ _| |_ ___ 
     / _ \| '_ \ || (_-<(_-< | |  __/ _` | __/ _ \
    /_/ \_\_.__/\_, /__/__/  | | |_ | (_| | ||  __/
                |__/          \_____|\__,_|\__\___|
    )" << RESET
         << endl;
    cout << "\n지킴이: 심연의 틈에 오신 것을 환영합니다, 명예를 쫓는 자여." << endl;
    cout << "지킴이: 이곳은 골드나 아이템을 주는 곳이 아닙니다. 오직 당신의 강함과 한계를 시험하는 곳이죠." << endl;
    cout << "지킴이: 당신의 최고 기록은 [ " << YELLOW << player.maxAbyssFloor << " F" << RESET << " ] 입니다." << endl;

    cout << "\n1. 심연으로 입장한다  2. 돌아간다\n선택: ";
    int choice;
    cin >> choice;
    if (choice != 1)
        return;

    int currentFloor = 1;
    bool inAbyss = true;

    while (inAbyss && player.hp > 0)
    {
        system("cls");

        // 층수에 따른 연출 변경
        string floorColor = RESET;
        if (currentFloor < 10)
        {
            floorColor = MAGENTA;
            cout << floorColor << R"(
    ~~~~~ (얕은 심연) ~~~~~
        )" << RESET
                 << endl;
        }
        else if (currentFloor < 30)
        {
            floorColor = RED;
            cout << floorColor << R"(
    ☠☠☠☠☠ (깊은 심연) ☠☠☠☠☠
        )" << RESET
                 << endl;
        }
        else
        {
            floorColor = "\033[90m";
            cout << floorColor << R"(
    ???????????????????????
        )" << RESET
                 << endl;
        } // 30층 이상은 흑백 (무의 공간)

        cout << floorColor << "\n===================================" << RESET << endl;
        cout << floorColor << "        [ 심연 " << currentFloor << " F ] 전투 시작!" << RESET << endl;
        cout << floorColor << "===================================\n"
             << RESET << endl;

        // 심연 몬스터 스폰 (던전보다 급격한 스탯 상승)
        // 몬스터 레벨 = (심연 층수 * 5) + 플레이어 레벨 (플레이어 레벨 비례)
        int monsterLevel = (currentFloor * 5) + player.level;
        unique_ptr<Monster> enemy(MonsterFactory::spawnMonster(monsterLevel, player.level));

        // 심연 전용 스탯 뻥튀기
        enemy->hp = (int)(enemy->hp * (1.5f + (currentFloor * 0.1f)));
        enemy->maxHp = enemy->hp;
        enemy->atk = (int)(enemy->atk * (1.2f + (currentFloor * 0.05f)));
        enemy->name = "심연의 " + enemy->name;

        cout << floorColor << enemy->name << RESET << " (이)가 어둠 속에서 나타납니다!" << endl;

        bool inCombat = true;
        while (inCombat && player.hp > 0 && enemy->hp > 0)
        {
            cout << "\n[플레이어] HP: " << GREEN << player.hp << "/" << player.maxHp << RESET
                 << " | MP: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
            cout << "[" << floorColor << enemy->name << RESET << "] HP: " << enemy->hp << "/" << enemy->maxHp << endl;

            cout << "1. 공격  2. 가방 (스킬/도망 불가! 오직 피지컬 승부!)\n선택: ";
            int bChoice;
            cin >> bChoice;
            system("cls");

            if (bChoice == 1)
            {
                int dmg = player.attack();
                if (rand() % 100 < 15)
                {
                    dmg = (int)(dmg * 1.8);
                    cout << YELLOW << "크리티컬!" << RESET << endl;
                }
                enemy->takeDamage(dmg);
                cout << YELLOW << dmg << "의 피해를 입혔습니다!" << RESET << endl;
            }
            else if (bChoice == 2)
            {
                player.openInventory();
            }
            else
            {
                cout << "잘못된 입력입니다." << endl;
            }

            if (enemy->hp > 0)
            {
                cout << "\n--- 적의 턴 ---" << endl;
                enemy->takeAction(player); // 몬스터 지능형 AI 연동
            }
        }

        // 결과 처리
        if (player.hp <= 0)
        {
            cout << RED << "\n심연의 어둠에 삼켜졌습니다... 지킴이가 당신을 심연 밖으로 끌어냅니다." << RESET << endl;
            player.hp = 1; // 죽지는 않고 1의 체력으로 마을 귀환
            inAbyss = false;
        }
        else
        {
            cout << GREEN << "\n"
                 << currentFloor << " F 클리어! 심연의 기운이 더욱 강해집니다." << RESET << endl;

            // 최고 기록 경신
            if (currentFloor > player.maxAbyssFloor)
            {
                player.maxAbyssFloor = currentFloor;
                cout << YELLOW << "!!! 최고 도달 층수 갱신 !!! [ " << player.maxAbyssFloor << " F ]" << RESET << endl;

                if (player.maxAbyssFloor == 30)
                {
                    cout << MAGENTA << "\n[알림] 명예 칭호 [심연의 정복자]를 획득했습니다!" << RESET << endl;
                }
            }

            cout << "\n1. 다음 층 도전 (Go)  2. 안전하게 돌아가기 (Stop)\n선택: ";
            int nextChoice;
            cin >> nextChoice;
            if (nextChoice == 2)
            {
                cout << GREEN << "\n정비 후 다시 도전하겠습니다." << RESET << endl;
                inAbyss = false;
            }
            else
            {
                currentFloor++;
            }
        }
    }

    if (player.hp > 0)
    {
        cout << "\n엔터를 누르면 마을 광장으로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }
}