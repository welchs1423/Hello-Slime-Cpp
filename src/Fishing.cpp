#include "../include/Fishing.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Fishing::visit(Player &player)
{
    bool inFishing = true;
    while (inFishing)
    {
        system("cls");
        cout << CYAN << "\n=== [ 평화로운 낚시터 ] ===" << RESET << endl;
        cout << "늙은 어부: 허허, 피비린내 나는 전투는 잠시 잊고 낚싯대나 드리우게나." << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

        cout << "\n1. 낚싯대 던지기 (미끼값: 100 G)" << endl;
        cout << "2. 마을로 돌아가기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (player.gold < 100)
            {
                cout << RED << "\n늙은 어부: 쯧쯧, 미끼 살 돈도 없으면서 무슨 낚시를 하겠다는 겐가!" << RESET << endl;
            }
            else
            {
                player.gold -= 100;
                cout << CYAN << "\n찌익- 퐁당!" << RESET << endl;
                cout << "물결이 잔잔하게 일렁입니다..." << endl;

                int roll = rand() % 1000;

                if (roll < 300)
                { // 30% 확률
                    cout << MAGENTA << "\n...낡은 장화가 낚였습니다. (쓰레기)" << RESET << endl;
                    cout << "어부에게 10G에 고철로 넘겼습니다." << endl;
                    player.gold += 10;
                }
                else if (roll < 750)
                { // 45% 확률
                    cout << GREEN << "\n오! 제법 통통한 [평범한 붕어]를 낚았습니다!" << RESET << endl;
                    cout << "시장에 150G에 팔아 소소한 이득을 챙겼습니다." << endl;
                    player.gold += 150;
                }
                else if (roll < 950)
                { // 20% 확률
                    cout << YELLOW << "\n묵직한 손맛!!! 번쩍이는 [황금 잉어]를 낚았습니다!!!" << RESET << endl;
                    cout << "상인들이 앞다투어 1000G에 사갔습니다!" << endl;
                    player.gold += 1000;
                }
                else
                { // 5% 확률
                    cout << RED << "\n!!! 낚싯대가 부러질 듯 미친듯이 휘어집니다 !!!" << RESET << endl;
                    cout << CYAN << "전설 속의 생물, [심해의 영물]을 낚아올렸습니다!" << RESET << endl;
                    cout << "영물을 그 자리에서 섭취하여 영구적으로 최대 체력이 20 증가합니다!" << endl;
                    player.maxHp += 20;
                    player.hp += 20;
                }
            }
        }
        else if (choice == 2)
        {
            cout << "낚싯대를 거두고 마을로 돌아갑니다..." << endl;
            inFishing = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inFishing)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}