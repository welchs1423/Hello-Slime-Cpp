#include "../include/Guild.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Guild::visit(Player& player){
    system("cls");
    cout << CYAN << "\n=== 모험가 길드 ===" << RESET << endl;

    // 진행중인 퀘스트가 없을 때
    if(player.activeQuestId == 0){
        cout << "길드장: \"오, 새로운 모험가인가? 마침 일거리가 있네.\"\n" << endl;
        cout << "1. [토벌] 초록 고블린 3마리 처치 (보상: 150G, 100EXP)" << endl;
        cout << "2. [토벌] 푸른 슬라임 5마리 처치 (보상: 100G, 50EXP)" << endl;
        cout << "3. [탐험] 던전 5층 도달하기 (보상: 300G, 철검 1개)" << endl;
        cout << "4. 돌아간다\n 선택: ";

        int choice;
        cin >> choice;

        if(choice >= 1 && choice <= 3){
            player.activeQuestId = choice;
            player.questProgress = 0;
            cout << GREEN << "\n길드장: \"좋아! 퀘스트를 수락했네. 행운을 비네!\"" << RESET << endl;
        }
    }
    // 진행중인 퀘스트가 있을 때
    else {
        cout << "길드장: \"임무는 어떻게 되어가나?\"\n" << endl;

        int target = 0;
        if (player.activeQuestId == 1) target = 3;
        else if (player.activeQuestId == 2) target = 5;
        else if (player.activeQuestId == 3) target = 1; // 5층 도달은 달성 시 1로 처리

        cout << "현재 임무 진척도: [" << player.questProgress << " / " << target << "]" << endl;

        // 퀘스트 완료 시 보상 지급!
        if (player.questProgress >= target) {
            cout << YELLOW << "\n 길드장: \"훌륭해! 임무를 완수했군. 여기 보상일세!\"" << RESET << endl;

            if(player.activeQuestId == 1){
                player.gold += 150; player.gainExp(100);
            } else if (player.activeQuestId == 2){
                player.gold += 100; player.gainExp(50);
            } else if (player.activeQuestId == 3){
                player.gold += 300;
                player.inventory.push_back(Item("철검",1,10,100));  // 가방에 철검 꽂아주기
                cout << GREEN << "가방에 [철검] 이 추가되었습니다!" << RESET << endl;
            }

            // 퀘스트 초기화
            player.activeQuestId = 0;
            player.questProgress = 0;
        } else {
            cout << RED << "\n길드장: \"아직 임무를 완수하지 못했군. 더 분발하게!\"" << RESET << endl;
            cout << "1. 퀘스트 포기하기 2. 계속 진행하기\n선택: ";
            int choice;
            cin >> choice;
            if (choice == 1){
                player.activeQuestId = 0;
                player.questProgress = 0;
                cout << "퀘스트를 포기했습니다." << endl;
            }
        }
    }

    cout << "\n엔터를 누르면 마을로 돌아갑니다...";
    cin.ignore();
    cin.get();
}