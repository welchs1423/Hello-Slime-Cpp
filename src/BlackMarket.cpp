#include "../include/BlackMarket.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void BlackMarket::visit(Player &player)
{
    bool inMarket = true;
    while (inMarket)
    {
        system("cls");
        cout << MAGENTA << "\n=== [ 뒷골목 암시장 ] ===" << RESET << endl;
        cout << "수상한 상인: 흐흐... 투기장에서 돈 좀 만지셨나 보군. 내 '특별한 상자' 한번 열어보겠나?" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

        cout << "\n1. 낡은 무기 상자 뽑기 (1,000 G)" << endl;
        cout << "2. 프리미엄 장비 가챠 (5,000 G) - [최소 3성 보장!]" << endl;
        cout << "3. 암시장 빠져나가기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1 || choice == 2)
        {
            int cost = (choice == 1) ? 1000 : 5000;

            if (player.gold < cost)
            {
                cout << RED << "\n수상한 상인: 돈도 없는 녀석이 어디서 기웃거려! 썩 꺼져!" << RESET << endl;
            }
            else
            {
                player.gold -= cost;
                cout << CYAN << "\n상자를 엽니다... 두구두구두구..." << RESET << endl;

                int roll = rand() % 1000; // 0 ~ 999 (0.1% 단위 정밀도)
                int stars = 1;
                string prefix = "";
                int baseStat = 0;

                // 확률 테이블 세팅
                if (choice == 1)
                { // 일반 뽑기
                    if (roll < 500)
                    {
                        stars = 1;
                        prefix = "\033[90m[1성: 낡은]\033[0m";
                        baseStat = 5;
                    } // 50%
                    else if (roll < 800)
                    {
                        stars = 2;
                        prefix = GREEN + "[2성: 평범한]" + RESET;
                        baseStat = 15;
                    } // 30%
                    else if (roll < 950)
                    {
                        stars = 3;
                        prefix = CYAN + "[3성: 희귀한]" + RESET;
                        baseStat = 30;
                    } // 15%
                    else if (roll < 995)
                    {
                        stars = 4;
                        prefix = MAGENTA + "[4성: 영웅의]" + RESET;
                        baseStat = 80;
                    } // 4.5%
                    else
                    {
                        stars = 5;
                        prefix = YELLOW + "[5성: 신화적인!!!]" + RESET;
                        baseStat = 200;
                    } // 0.5%
                }
                else
                { // 프리미엄 뽑기 (최소 3성)
                    if (roll < 600)
                    {
                        stars = 3;
                        prefix = CYAN + "[3성: 희귀한]" + RESET;
                        baseStat = 30;
                    } // 60%
                    else if (roll < 950)
                    {
                        stars = 4;
                        prefix = MAGENTA + "[4성: 영웅의]" + RESET;
                        baseStat = 80;
                    } // 35%
                    else
                    {
                        stars = 5;
                        prefix = YELLOW + "[5성: 신화적인!!!]" + RESET;
                        baseStat = 200;
                    } // 5%
                }

                // 장비 종류 랜덤 결정 (0: 무기, 1: 방어구)
                int equipType = rand() % 2;
                string baseName = (equipType == 0) ? " 검" : " 갑옷";
                int eTypeNum = (equipType == 0) ? 1 : 2;

                // 최종 스탯 계산 (기본 스탯 + 랜덤 추가 스탯)
                int finalStat = baseStat + (rand() % (baseStat / 2 + 1));
                int value = finalStat * 50; // 상점 판매가

                string finalName = prefix + baseName;

                // 이펙트 출력
                if (stars >= 4)
                    cout << MAGENTA << "\n!!! 번쩍이는 광채가 뿜어져 나옵니다 !!!" << RESET << endl;
                if (stars == 5)
                    cout << YELLOW << "세계의 운명이 담긴듯한 엄청난 기운입니다!!!" << RESET << endl;

                cout << "\n획득 장비: " << finalName << " (능력치: +" << finalStat << ")" << endl;

                // 가방에 넣기
                player.inventory.push_back(Item(finalName, eTypeNum, finalStat, value));
                cout << GREEN << "장비가 가방에 보관되었습니다!" << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "뒷골목을 조용히 빠져나옵니다..." << endl;
            inMarket = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inMarket)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}