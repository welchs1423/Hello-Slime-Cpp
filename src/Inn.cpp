#include "../include/Inn.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void Inn::visit(Player &player)
{
    bool inInn = true;
    while (inInn)
    {
        system("cls");
        cout << CYAN << "\n=== [ 달빛 여관 & 지하 경주장 ] ===" << RESET << endl;
        cout << "여관주인: 쉬러 왔어? 아니면... 지하에서 '한 탕' 하러 왔어?" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
        cout << "[ 체력 ]: " << GREEN << player.hp << "/" << player.maxHp << RESET << endl;

        cout << "\n1. 방 잡고 푹 쉬기 (50G - HP/MP 100% 회복)" << endl;
        cout << "2. 지하 슬라임 경주장 입장 (도박장)" << endl;
        cout << "3. 여관 나가기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (player.gold >= 50)
            {
                player.gold -= 50;
                player.heal();
                player.restoreMp();
                cout << GREEN << "따뜻한 침대에서 푹 쉬었습니다. (HP/MP 100% 회복!)" << RESET << endl;
            }
            else
            {
                cout << RED << "여관주인: 돈도 없는 게 어디서 자려고! 썩 나가!" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            system("cls");
            cout << MAGENTA << "\n=== [ 불법 슬라임 경주장 ] ===" << RESET << endl;
            cout << "진행자: 자자, 오늘의 승자는 과연 누구일지! 돈을 거십시오!" << endl;
            cout << "[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

            cout << "\n1. 레드 슬라임   (배당 2.0배 - 무난한 픽)" << endl;
            cout << "2. 블루 슬라임   (배당 3.0배 - 다크호스)" << endl;
            cout << "3. 킹 슬라임     (배당 1.5배 - 안정적인 우승 후보)" << endl;
            cout << "4. 맹독 슬라임   (배당 5.0배 - 한방 역배!)" << endl;
            cout << "0. 쫄려서 나간다\n\n베팅할 슬라임 번호: ";

            int pick;
            cin >> pick;
            if (pick == 0)
                continue;
            if (pick < 1 || pick > 4)
            {
                cout << RED << "잘못된 번호입니다." << RESET << endl;
                continue;
            }

            cout << "베팅할 금액을 입력하세요: ";
            int bet;
            cin >> bet;

            if (bet <= 0 || bet > player.gold)
            {
                cout << RED << "진행자: 장난치지 마십시오! 가진 돈 안에서만 거세요." << RESET << endl;
            }
            else
            {
                player.gold -= bet;
                cout << CYAN << "\n경주 시작! 엎치락뒤치락 치열합니다..." << RESET << endl;

                // 경주 결과 시뮬레이션
                int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
                int winner = 0;
                for (int i = 0; i < 15; ++i)
                {
                    p1 += rand() % 4;
                    p2 += rand() % 5;
                    p3 += rand() % 3 + 1;
                    p4 += rand() % 6;
                    if (p1 >= 20)
                    {
                        winner = 1;
                        break;
                    }
                    if (p2 >= 20)
                    {
                        winner = 2;
                        break;
                    }
                    if (p3 >= 20)
                    {
                        winner = 3;
                        break;
                    }
                    if (p4 >= 20)
                    {
                        winner = 4;
                        break;
                    }
                }
                if (winner == 0)
                    winner = (rand() % 4) + 1; // 무승부 방지

                string wName = (winner == 1) ? "레드 슬라임" : (winner == 2) ? "블루 슬라임"
                                                           : (winner == 3)   ? "킹 슬라임"
                                                                             : "맹독 슬라임";
                cout << YELLOW << "결승선 통과!!! 오늘의 우승은 [" << wName << "] 입니다!!!" << RESET << endl;

                if (pick == winner)
                {
                    float odds = (winner == 1) ? 2.0f : (winner == 2) ? 3.0f
                                                    : (winner == 3)   ? 1.5f
                                                                      : 5.0f;
                    int prize = (int)(bet * odds);
                    player.gold += prize;
                    cout << GREEN << "축하합니다! 베팅에 성공하여 " << prize << " G를 획득했습니다!" << RESET << endl;
                }
                else
                {
                    cout << RED << "아쉽네요... 베팅금을 모두 잃었습니다." << RESET << endl;
                }
            }
        }
        else if (choice == 3)
        {
            cout << "여관문을 열고 나섭니다..." << endl;
            inInn = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inInn)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}