#include "../include/GameManager.h"
#include "../include/Colors.h"
#include "../include/Inn.h"
#include "../include/Guild.h"
#include "../include/Bank.h"
#include "../include/Blacksmith.h"
#include "../include/MagicTower.h"
#include "../include/Arena.h"
#include "../include/BlackMarket.h"
#include "../include/Raid.h"
#include "../include/Fishing.h"
#include "../include/Estate.h"
#include "../include/Alchemy.h"
#include "../include/Mine.h"
#include "../include/Abyss.h" // 심연의 틈 추가
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

        // UI 4열 그리드 확장, 심연(17번) 추가
        cout << "--------------------------------------------------------------\n";
        cout << " 1. 던전탐험   |  2. 피의투기장 |  3. 낚시터     |  4. 광산/세공소 \n";
        cout << " 5. 마을상점   |  6. 뒷골목암시장 |  7. 대장간     |  8. 마법탑     \n";
        cout << " 9. 마을은행   | 10. 모험가길드  | 11. 여관/도박  | 12. 개인영지(집) \n";
        cout << " 13. 연금술공방| 14. 보스레이드  | 15. 가방열기   | 16. 스탯분배   \n";
        cout << MAGENTA << " 17. 심연의틈" << RESET << CYAN << "   | 18. 게임저장   " << RESET << "| 0. 종료        | \n";
        cout << "--------------------------------------------------------------\n선택: ";

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
            Fishing::visit(player);
        else if (townChoice == 4)
            Mine::visit(player);
        else if (townChoice == 5)
            shop.visit(player);
        else if (townChoice == 6)
            BlackMarket::visit(player);
        else if (townChoice == 7)
            Blacksmith::visit(player);
        else if (townChoice == 8)
            MagicTower::visit(player);
        else if (townChoice == 9)
            Bank::visit(player);
        else if (townChoice == 10)
            Guild::visit(player);
        else if (townChoice == 11)
            Inn::visit(player);
        else if (townChoice == 12)
            Estate::visit(player);
        else if (townChoice == 13)
            Alchemy::visit(player);
        else if (townChoice == 14)
            Raid::visit(player);
        else if (townChoice == 15)
            player.openInventory();
        else if (townChoice == 16)
            player.allocateStats();
        else if (townChoice == 17)
            Abyss::visit(player); // 심연의 틈 방문
        else if (townChoice == 18)
        {
            system("cls");
            player.save();
            cout << "\n저장 완료! 엔터를 누르세요.";
            cin.ignore();
            cin.get();
        }
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