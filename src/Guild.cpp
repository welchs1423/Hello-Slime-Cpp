#include "../include/Guild.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Guild::visit(Player &player)
{
    bool inGuild = true;
    while (inGuild)
    {
        system("cls");
        cout << CYAN << "\n=== [ 모험가 길드 ] ===" << RESET << endl;
        cout << "길드장: 오, 왔는가! 오늘은 어떤 용무로 찾아왔지? 현상금 사냥인가, 아니면 동료를 구하러 왔나?" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

        cout << "\n1. 의뢰 게시판 (퀘스트 수락 및 현상금 수령)" << endl;
        cout << "2. 펫 분양소 (전투 보조 동료 고용)" << endl;
        cout << "3. 환생의 제단 (Lv.50 이상 전용)" << endl;
        cout << "4. 길드 나서기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            cout << YELLOW << "\n=== [ 길드 의뢰 게시판 ] ===" << RESET << endl;
            // 퀘스트가 없을 때
            if (player.activeQuestId == 0)
            {
                cout << "1. 초록 고블린 토벌 (보상: 1000 G, 목표: 3마리)" << endl;
                cout << "2. 푸른 슬라임 토벌 (보상: 800 G, 목표: 5마리)" << endl;
                cout << "0. 취소\n수락할 의뢰 번호: ";
                int qChoice;
                cin >> qChoice;
                if (qChoice == 1)
                {
                    player.activeQuestId = 1;
                    player.questProgress = 0;
                    cout << GREEN << "초록 고블린 토벌 의뢰를 수락했습니다! (던전에서 사냥하세요)" << RESET << endl;
                }
                else if (qChoice == 2)
                {
                    player.activeQuestId = 2;
                    player.questProgress = 0;
                    cout << GREEN << "푸른 슬라임 토벌 의뢰를 수락했습니다! (던전에서 사냥하세요)" << RESET << endl;
                }
            }
            // 퀘스트 진행 중일 때
            else
            {
                int target = (player.activeQuestId == 1) ? 3 : 5;
                string targetName = (player.activeQuestId == 1) ? "초록 고블린" : "푸른 슬라임";
                cout << "현재 진행 중인 의뢰: [" << targetName << " 토벌]" << endl;
                cout << "진행도: " << player.questProgress << " / " << target << " 마리" << endl;

                if (player.questProgress >= target)
                {
                    cout << YELLOW << "\n길드장: 오오! 훌륭하게 완수했군! 여기 약속한 현상금일세!" << RESET << endl;
                    int reward = (player.activeQuestId == 1) ? 1000 : 800;
                    player.gold += reward;
                    player.activeQuestId = 0; // 퀘스트 초기화
                    player.questProgress = 0;
                    cout << GREEN << reward << " G를 획득했습니다!" << RESET << endl;
                }
                else
                {
                    cout << RED << "\n길드장: 아직 목표치를 채우지 못했어. 어서 던전으로 다녀오게!" << RESET << endl;
                }
            }
        }
        else if (choice == 2)
        {
            system("cls");
            cout << MAGENTA << "\n=== [ 펫 분양소 ] ===" << RESET << endl;
            cout << "현재 동행 펫: " << (player.activePet == 1 ? "전투 늑대" : player.activePet == 2 ? "치유의 요정"
                                                                                                     : "없음")
                 << endl;
            cout << "[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

            cout << "\n1. 전투 늑대 고용 (2000 G) - 매 턴 적에게 고정 피해!" << endl;
            cout << "2. 치유의 요정 고용 (2500 G) - 매 턴 플레이어 체력 회복!" << endl;
            cout << "0. 취소\n선택: ";
            int pChoice;
            cin >> pChoice;

            if (pChoice == 1)
            {
                if (player.gold >= 2000)
                {
                    player.gold -= 2000;
                    player.activePet = 1;
                    cout << GREEN << "듬직한 [전투 늑대]가 당신을 따릅니다!" << RESET << endl;
                }
                else
                    cout << RED << "골드가 부족합니다." << RESET << endl;
            }
            else if (pChoice == 2)
            {
                if (player.gold >= 2500)
                {
                    player.gold -= 2500;
                    player.activePet = 2;
                    cout << GREEN << "신비로운 [치유의 요정]이 당신과 동행합니다!" << RESET << endl;
                }
                else
                    cout << RED << "골드가 부족합니다." << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            player.doRebirth(); // Player.cpp 에 구현된 환생 함수 호출
        }
        else if (choice == 4)
        {
            cout << "길드 문을 열고 나섭니다..." << endl;
            inGuild = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inGuild)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}