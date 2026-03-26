#include "../include/Shop.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Shop::visit(Player &player)
{
    bool shopping = true;
    while (shopping)
    {
        system("cls");
        cout << CYAN << "\n=== 마을 상점 ===" << RESET << endl;
        player.printStatus();
        cout << "\n1. 체력 포션 (30G)\n2. 마나 포션 (30G)\n3. 미스터리 박스 (100G)\n4. 상점 나가기\n선택: ";
        int choice;
        cin >> choice;
        if (choice == 1 && player.gold >= 30)
        {
            player.gold -= 30;
            player.inventory.push_back(Item("체력 포션", 3, 50, 30));
        }
        else if (choice == 2 && player.gold >= 30)
        {
            player.gold -= 30;
            player.inventory.push_back(Item("마나 포션", 4, 50, 30));
        }
        else if (choice == 3 && player.gold >= 100)
        {
            player.gold -= 100;
            int roll = rand() % 100;
            if (roll < 20)
            {
                player.inventory.push_back(Item("붉은 루비", 6, 20, 500));
                cout << RED << "축하합니다! [붉은 루비]를 획득했습니다!" << RESET << endl;
            }
            else if (roll < 40)
            {
                player.inventory.push_back(Item("푸른 사파이어", 6, 30, 500));
                cout << CYAN << "축하합니다! [푸른 사파이어]를 획득했습니다!" << RESET << endl;
            }
            else
            {
                cout << "평범한 돌멩이가 나왔습니다." << endl;
            }
            cin.ignore();
            cin.get();
        }
        else if (choice == 4)
            shopping = false;
    }
}