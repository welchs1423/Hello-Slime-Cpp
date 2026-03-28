#include "../include/GameManager.h"
#include "../include/Colors.h"
#include "../include/Inn.h"
#include "../include/Guild.h"
#include "../include/Bank.h"
#include "../include/Blacksmith.h"
#include "../include/MagicTower.h"
#include "../include/Arena.h"
#include "../include/BlackMarket.h" // 암시장 추가
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

        // UI 정렬 및 암시장(12번) 추가
        cout << " 1. 던전 탐험      2. 피의 투기장    3. 여관/도박장    4. 모험가 길드\n";
        cout << " 5. 마을 상점      6. 마을 은행      7. 드워프 대장간  8. 신비한 마법탑\n";
        cout << " 9. 가방 열기     10. 스탯 분배     11. 게임 저장     12. 뒷골목 암시장\n";
        cout << " 0. 게임 종료\n\n선택: ";

        int townChoice;
        cin >> townChoice;

        if (townChoice == 1)
        {
            system("cls");
            cout << "\n=== 던전 난이도 선택 ===" << endl;
            cout << "1. 쉬움 (적 스탯 80%)\n2. 보통 (적 스탯 100%)\n3. 어려움 (적 스탯 150%)\n0. 취소\n선택: ";
            int diffChoice;
            cin >> diffChoice;
            if (diffChoice >= 1 && diffChoice <= 3)
                battle.start(player, diffChoice);
        }
        else if (townChoice == 2)
            Arena::visit(player);
        else if (townChoice == 3)
            Inn::visit(player);
        else if (townChoice == 4)
            Guild::visit(player);
        else if (townChoice == 5)
            shop.visit(player);
        else if (townChoice == 6)
            Bank::visit(player);
        else if (townChoice == 7)
            Blacksmith::visit(player);
        else if (townChoice == 8)
            MagicTower::visit(player);
        else if (townChoice == 9)
            player.openInventory();
        else if (townChoice == 10)
            player.allocateStats();
        else if (townChoice == 11)
        {
            system("cls");
            player.save();
            cout << "\n저장 완료! 엔터를 누르세요.";
            cin.ignore();
            cin.get();
        }
        else if (townChoice == 12)
            BlackMarket::visit(player); // 암시장 방문
        else if (townChoice == 0)
        {
            system("cls");
            cout << "진행 상황을 안전하게 저장합니다..." << endl;
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
        cout << "\n플레이어가 쓰러졌습니다... 게임 오버." << endl;
}