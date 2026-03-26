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
        cout << CYAN << "\n=== 모험가 길드 ===" << RESET << endl;
        cout << "길드 마스터: 오, 새로운 의뢰를 찾으러 왔는가?" << endl;

        cout << "\n[ 현재 진행 중인 퀘스트 ]" << endl;
        if (player.activeQuestId == 0)
            cout << "진행 중인 퀘스트가 없습니다." << endl;
        else if (player.activeQuestId == 1)
            cout << "- 초록 고블린 3마리 토벌 (" << player.questProgress << "/3)" << endl;
        else if (player.activeQuestId == 2)
            cout << "- 푸른 슬라임 5마리 토벌 (" << player.questProgress << "/5)" << endl;
        else if (player.activeQuestId == 3)
            cout << "- 던전 5층 도달 (" << player.questProgress << "/1)" << endl;

        cout << "\n1. 퀘스트 게시판 보기" << endl;
        cout << "2. 퀘스트 보상 받기" << endl;
        cout << MAGENTA << "3. 초월 환생 (Max Lv.50 필요, 영구 스탯 보너스)" << RESET << endl;
        cout << GREEN << "4. 펫 분양소 (동행 펫 고용)" << RESET << endl;
        cout << "5. 길드 나가기\n선택: ";

        int choice;
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
        {
            if (player.activeQuestId != 0)
            {
                cout << RED << "이미 진행 중인 퀘스트가 있습니다!" << RESET << endl;
                cout << "포기하시겠습니까? (1. 예 / 2. 아니오): ";
                int giveUp;
                cin >> giveUp;
                if (giveUp == 1)
                {
                    player.activeQuestId = 0;
                    player.questProgress = 0;
                    cout << YELLOW << "퀘스트를 포기했습니다." << RESET << endl;
                }
            }
            else
            {
                cout << YELLOW << "\n=== 퀘스트 게시판 ===" << RESET << endl;
                cout << "1. [토벌] 초록 고블린 3마리 처치 (보상: 150G, 100 EXP)" << endl;
                cout << "2. [토벌] 푸른 슬라임 5마리 처치 (보상: 100G, 80 EXP)" << endl;
                cout << "3. [탐험] 던전 5층 돌파 (보상: 300G, 200 EXP)" << endl;
                cout << "0. 취소\n수주할 퀘스트 번호를 선택하세요: ";
                int qChoice;
                cin >> qChoice;
                if (qChoice >= 1 && qChoice <= 3)
                {
                    player.activeQuestId = qChoice;
                    player.questProgress = 0;
                    cout << GREEN << "퀘스트 수주 완료!" << RESET << endl;
                }
                else if (qChoice != 0)
                    cout << RED << "잘못된 번호입니다." << RESET << endl;
            }
            break;
        }
        case 2:
        {
            if (player.activeQuestId == 0)
                cout << RED << "완료할 퀘스트가 없습니다!" << RESET << endl;
            else
            {
                bool isCompleted = false;
                int rewardGold = 0;
                int rewardExp = 0;
                if (player.activeQuestId == 1 && player.questProgress >= 3)
                {
                    isCompleted = true;
                    rewardGold = 150;
                    rewardExp = 100;
                }
                else if (player.activeQuestId == 2 && player.questProgress >= 5)
                {
                    isCompleted = true;
                    rewardGold = 100;
                    rewardExp = 80;
                }
                else if (player.activeQuestId == 3 && player.questProgress >= 1)
                {
                    isCompleted = true;
                    rewardGold = 300;
                    rewardExp = 200;
                }

                if (isCompleted)
                {
                    cout << GREEN << "길드 마스터: 훌륭하게 해냈구만! 여기 보상일세." << RESET << endl;
                    cout << YELLOW << rewardGold << " 골드와 " << rewardExp << " 경험치를 획득했습니다!" << RESET << endl;
                    player.gold += rewardGold;
                    player.gainExp(rewardExp);
                    player.activeQuestId = 0;
                    player.questProgress = 0;
                }
                else
                    cout << YELLOW << "길드 마스터: 아직 의뢰를 완수하지 못했구만. 분발하게!" << RESET << endl;
            }
            break;
        }
        case 3:
        {
            if (player.level < 50)
            {
                cout << RED << "길드 마스터: 자네는 아직 환생을 감당할 그릇이 안 되네. 레벨 50을 달성하고 오게나." << RESET << endl;
            }
            else
            {
                cout << MAGENTA << "길드 마스터: 진정으로 육체를 버리고 새로운 경지에 오르겠는가?\n(경고: 레벨과 던전 진행도가 1로 초기화되며, 영구적인 기본 스탯 보너스를 얻습니다.)" << RESET << endl;
                cout << "1. 환생한다 / 2. 그만둔다\n선택: ";
                int rebirthChoice;
                cin >> rebirthChoice;
                if (rebirthChoice == 1)
                {
                    player.doRebirth();
                }
                else
                {
                    cout << "환생을 취소했습니다." << endl;
                }
            }
            break;
        }
        case 4:
        {
            cout << GREEN << "\n=== 펫 분양소 ===" << RESET << endl;
            cout << "조련사: 던전 탐험을 도와줄 든든한 동료를 찾아보시겠소? (분양가: 1000G)" << endl;
            cout << "현재 보유 골드: " << YELLOW << player.gold << "G" << RESET << endl;
            cout << "1. 전투 늑대 (매 턴마다 적에게 고정 피해를 입힘)" << endl;
            cout << "2. 치유의 요정 (매 턴마다 플레이어의 체력을 회복시킴)" << endl;
            cout << "0. 취소\n선택: ";
            int petChoice;
            cin >> petChoice;
            if (petChoice == 1 || petChoice == 2)
            {
                if (player.gold >= 1000)
                {
                    player.gold -= 1000;
                    player.activePet = petChoice;
                    if (petChoice == 1)
                        cout << GREEN << "전투 늑대가 동행을 시작합니다!" << RESET << endl;
                    else
                        cout << GREEN << "치유의 요정이 동행을 시작합니다!" << RESET << endl;
                }
                else
                {
                    cout << RED << "골드가 부족합니다!" << RESET << endl;
                }
            }
            break;
        }
        case 5:
            cout << "길드를 나섭니다..." << endl;
            inGuild = false;
            break;
        default:
            cout << RED << "잘못된 입력입니다." << RESET << endl;
            break;
        }

        if (inGuild)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}