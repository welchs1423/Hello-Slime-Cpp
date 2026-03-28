#include "../include/Temple.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Temple::visit(Player &player)
{
    bool inTemple = true;
    while (inTemple)
    {
        system("cls");
        cout << CYAN << "\n=== [ 성스러운 신의 신전 (Temple of the Gods) ] ===" << RESET << endl;

        if (!player.isAwakened)
        {
            cout << "대사제: 빛의 인도를 따라오셨군요, 필멸자여. 인간의 굴레를 벗어던질 준비가 되셨습니까?" << endl;
            cout << "대사제: 신의 축복을 받기 위해서는 " << YELLOW << "50,000 G" << RESET << "의 봉헌금이 필요합니다." << endl;
            cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

            cout << "\n1. [전쟁의 신]의 축복을 받는다 (영구 STR +50, MAX HP +200)" << endl;
            cout << "2. [지혜의 신]의 축복을 받는다 (영구 INT +50, MAX MP +100)" << endl;
            cout << "3. 아직 마음의 준비가 되지 않았습니다 (돌아가기)\n선택: ";

            int choice;
            cin >> choice;

            if (choice == 1 || choice == 2)
            {
                if (player.gold >= 50000)
                {
                    player.gold -= 50000;
                    player.isAwakened = true;

                    cout << MAGENTA << "\n==================================================" << RESET << endl;
                    cout << YELLOW << " 하늘에서 눈부신 빛의 기둥이 당신을 감쌉니다!!!" << RESET << endl;

                    if (choice == 1)
                    {
                        player.str += 50;
                        player.maxHp += 200;
                        player.hp = player.maxHp;
                        player.name = "[전쟁의 사도] " + player.name;
                        cout << RED << " 끓어오르는 투기가 온몸을 지배합니다! (STR +50, HP +200)" << RESET << endl;
                    }
                    else
                    {
                        player.intel += 50;
                        player.maxMp += 100;
                        player.mp = player.maxMp;
                        player.name = "[지혜의 현자] " + player.name;
                        cout << BLUE << " 우주의 진리가 머릿속에 흘러들어옵니다! (INT +50, MP +100)" << RESET << endl;
                    }
                    cout << MAGENTA << "==================================================\n"
                         << RESET << endl;
                    cout << GREEN << "2차 각성에 성공했습니다! 칭호가 변경되었습니다!" << RESET << endl;
                }
                else
                {
                    cout << RED << "\n대사제: 쯧쯧... 신에 대한 믿음(골드)이 부족하군요. 돈을 더 모아오십시오." << RESET << endl;
                }
            }
            else if (choice == 3)
            {
                cout << "신전을 경건한 발걸음으로 나섭니다..." << endl;
                inTemple = false;
            }
            else
            {
                cout << RED << "잘못된 입력입니다." << RESET << endl;
            }
        }
        else
        {
            // 이미 각성한 경우
            cout << "대사제: 오오... 위대한 " << player.name << " 님이시여, 신의 가호가 함께하길." << endl;
            cout << "\n1. 성수 마시기 (무료 풀 회복)" << endl;
            cout << "2. 신전 나서기\n선택: ";

            int bChoice;
            cin >> bChoice;
            if (bChoice == 1)
            {
                player.hp = player.maxHp;
                player.mp = player.maxMp;
                cout << GREEN << "\n성스러운 샘물을 마시고 몸과 마음이 완벽하게 정화되었습니다! (100% 회복)" << RESET << endl;
            }
            else if (bChoice == 2)
            {
                cout << "신전을 경건한 발걸음으로 나섭니다..." << endl;
                inTemple = false;
            }
            else
            {
                cout << RED << "잘못된 입력입니다." << RESET << endl;
            }
        }

        if (inTemple)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}