#include "GameManager.h"
#include "Colors.h"
#include "../include/Inn.h"
#include "../include/Guild.h"
#include <iostream>
#include <cstdlib>

using namespace std;

GameManager::GameManager() { isPlaying = true; }

void GameManager::run()
{
    system("cls");
    cout << CYAN << "=== 슬라임 헌터 RPG ===" << RESET << endl;
    cout << "1. 새로 하기  2. 이어 하기\n선택: ";
    int startChoice;
    cin >> startChoice;

    if (startChoice == 1)
        player.chooseClass();
    else if (startChoice == 2)
        player.load();

    while (isPlaying && player.hp > 0)
    {
        system("cls");
        cout << "\n=== 마을 광장 ===" << endl;
        player.printStatus();

        cout << "1. 던전 입장  2. 상점 방문  3. 여관 휴식 (30G)  4. 모험가 길드  5. 가방 열기  6. 스탯 분배  7. 스탯 초기화 (500G)  8. 게임 저장  9. 게임 종료\n선택: ";

        int townChoice;
        cin >> townChoice;

        if (townChoice == 1)
        {
            system("cls");
            cout << "\n=== 던전 난이도 선택 ===" << endl;
            cout << "1. 쉬움 (적 능력치 80%, 보상 80%)" << endl;
            cout << "2. 보통 (적 능력치 100%, 보상 100%)" << endl;
            cout << "3. 어려움 (적 능력치 150%, 보상 150%)" << endl;
            cout << "0. 마을로 돌아가기\n선택: ";

            int diffChoice;
            cin >> diffChoice;

            if (diffChoice >= 1 && diffChoice <= 3)
            {
                battle.start(player, diffChoice);
            }
            else if (diffChoice != 0)
            {
                cout << "잘못된 입력입니다. 보통 난이도로 진입합니다." << endl;
                battle.start(player, 2);
            }
        }
        else if (townChoice == 2)
            shop.visit(player);
        else if (townChoice == 3)
            Inn::visit(player);
        else if (townChoice == 4)
            Guild::visit(player);
        else if (townChoice == 5)
            player.openInventory();
        else if (townChoice == 6)
            player.allocateStats();
        else if (townChoice == 7)
        {
            system("cls");
            player.resetStats();
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
        else if (townChoice == 8)
        {
            system("cls");
            player.save();
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
        else if (townChoice == 9)
        {
            system("cls");
            cout << "데이터 유실을 방지하기 위해 진행 상황을 안전하게 저장합니다..." << endl;
            player.save();
            cout << "게임을 종료합니다. 안녕히 가세요!" << endl;
            isPlaying = false;
        }
        else
        {
            system("cls");
            cout << "잘못된 입력입니다." << endl;
        }
    }
    if (player.hp <= 0)
    {
        cout << "\n플레이어가 쓰러졌습니다... 게임 오버." << endl;
    }
}