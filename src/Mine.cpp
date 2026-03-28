#include "../include/Mine.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void Mine::visit(Player &player)
{
    bool inMine = true;
    int pickaxeDurability = 0;

    while (inMine)
    {
        system("cls");
        cout << YELLOW << "\n=== [ 버려진 드워프 광산 & 세공소 ] ===" << RESET << endl;
        cout << "광부: 쾅! 쾅! 곡괭이 하나면 일확천금도 꿈이 아니지! 물론 빈털터리가 될 수도 있고 껄껄!" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
        cout << "[ 남은 곡괭이 내구도 ]: " << CYAN << pickaxeDurability << RESET << endl;

        cout << "\n1. 고급 곡괭이 구매 (500 G / 내구도 10)" << endl;
        cout << "2. 광맥 캐기 (내구도 1 소모)" << endl;
        cout << "3. 장비에 보석 세공하기 (소켓 장착)" << endl;
        cout << "4. 광산 나서기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (player.gold >= 500)
            {
                player.gold -= 500;
                pickaxeDurability += 10;
                cout << GREEN << "\n튼튼한 고급 곡괭이를 구매했습니다! (내구도 +10)" << RESET << endl;
            }
            else
            {
                cout << RED << "\n광부: 돈도 없이 광물을 캐겠다고? 썩 꺼져!" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            if (pickaxeDurability > 0)
            {
                pickaxeDurability--;
                cout << CYAN << "\n깡! 깡! 쨍그랑..." << RESET << endl;
                int roll = rand() % 100;

                if (roll < 40)
                {
                    cout << "\n먼지만 날립니다... [돌멩이]를 캤습니다. (가치 없음)" << endl;
                }
                else if (roll < 70)
                {
                    cout << GREEN << "\n오! [철광석]을 캤습니다! (100 G 획득)" << RESET << endl;
                    player.gold += 100;
                }
                else if (roll < 90)
                {
                    cout << YELLOW << "\n눈이 부십니다! [금괴]를 발견했습니다! (500 G 획득)" << RESET << endl;
                    player.gold += 500;
                }
                else if (roll < 95)
                {
                    cout << RED << "\n!!! 뜨거운 열기가 느껴집니다 !!! [루비(공격력 보석)]를 발견했습니다!" << RESET << endl;
                    player.inventory.push_back(Item("루비(보석)", 6, 1, 1000)); // type 6 = 보석
                }
                else
                {
                    cout << BLUE << "\n!!! 차가운 한기가 느껴집니다 !!! [사파이어(방어력 보석)]를 발견했습니다!" << RESET << endl;
                    player.inventory.push_back(Item("사파이어(보석)", 6, 2, 1000)); // type 6 = 보석
                }
            }
            else
            {
                cout << RED << "\n곡괭이가 없습니다! 상점에서 먼저 구매하세요." << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            system("cls");
            cout << MAGENTA << "\n[ 보석 세공소 ]" << RESET << endl;
            cout << "세공사: 장비에 마력을 불어넣어 주지! 어떤 장비에 보석을 박을 텐가?" << endl;

            vector<int> equipableIndices;
            for (size_t i = 0; i < player.inventory.size(); ++i)
            {
                if (player.inventory[i].type == 1 || player.inventory[i].type == 2)
                    equipableIndices.push_back(i);
            }

            if (equipableIndices.empty())
            {
                cout << RED << "\n세공할 장비(무기/방어구)가 가방에 없습니다!" << RESET << endl;
            }
            else
            {
                cout << "\n[ 세공 가능한 장비 목록 ]" << endl;
                for (size_t i = 0; i < equipableIndices.size(); ++i)
                {
                    int idx = equipableIndices[i];
                    Item &item = player.inventory[idx];
                    string gemName = (item.socketGem == 1) ? RED + " [루비 장착됨]" + RESET : (item.socketGem == 2) ? BLUE + " [사파이어 장착됨]" + RESET
                                                                                                                    : " [빈 소켓]";
                    cout << i + 1 << ". " << item.name << gemName << endl;
                }
                cout << "0. 취소\n장비를 선택하세요: ";
                int eqChoice;
                cin >> eqChoice;

                if (eqChoice > 0 && eqChoice <= equipableIndices.size())
                {
                    int targetIdx = equipableIndices[eqChoice - 1];
                    Item &targetItem = player.inventory[targetIdx];

                    vector<int> gemIndices;
                    cout << "\n[ 보유 중인 보석 목록 ]" << endl;
                    int displayIdx = 1;
                    for (size_t i = 0; i < player.inventory.size(); ++i)
                    {
                        if (player.inventory[i].type == 6)
                        {
                            gemIndices.push_back(i);
                            cout << displayIdx++ << ". " << player.inventory[i].name << endl;
                        }
                    }

                    if (gemIndices.empty())
                    {
                        cout << RED << "\n가방에 장착할 보석이 없습니다! 광산을 파보세요." << RESET << endl;
                    }
                    else
                    {
                        cout << "0. 취소\n장착할 보석을 선택하세요: ";
                        int gemChoice;
                        cin >> gemChoice;

                        if (gemChoice > 0 && gemChoice <= gemIndices.size())
                        {
                            int gemIdx = gemIndices[gemChoice - 1];
                            Item &gemItem = player.inventory[gemIdx];

                            if (gemItem.name.find("루비") != string::npos)
                                targetItem.socketGem = 1;
                            else
                                targetItem.socketGem = 2;

                            cout << GREEN << "\n성공적으로 [" << targetItem.name << "]에 [" << gemItem.name << "]를 세공했습니다!" << RESET << endl;

                            // 장착한 보석은 가방에서 삭제
                            player.inventory.erase(player.inventory.begin() + gemIdx);
                        }
                    }
                }
            }
        }
        else if (choice == 4)
        {
            cout << "광산을 빠져나옵니다..." << endl;
            inMine = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inMine)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}