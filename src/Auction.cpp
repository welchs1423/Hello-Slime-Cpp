#include "../include/Auction.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void Auction::visit(Player &player)
{
    system("cls");
    cout << YELLOW << "\n=== [ 제국 그랜드 경매장 (Grand Auction House) ] ===" << RESET << endl;
    cout << "경매사: 제국 최고의 진귀한 물건들이 모이는 곳입니다. 지갑은 두둑히 챙겨오셨겠죠?" << endl;

    // 경매에 올라올 아이템 랜덤 생성 (4성 ~ 5성급)
    int roll = rand() % 100;
    string itemName;
    int itemType = rand() % 2 + 1; // 1: 무기, 2: 방어구
    int stat = 0;
    int startingBid = 0;
    int npcMaxBid = 0;

    if (roll < 70)
    {
        itemName = MAGENTA + "[4성: 잊혀진 제국의]" + RESET + (itemType == 1 ? " 검" : " 갑옷");
        stat = 100 + rand() % 50;
        startingBid = 10000;
        npcMaxBid = 20000 + rand() % 30000; // NPC는 최대 2만~5만까지 부름
    }
    else
    {
        itemName = YELLOW + "[5성: 신을 죽인 자의]" + RESET + (itemType == 1 ? " 마검" : " 성갑");
        stat = 300 + rand() % 100;
        startingBid = 50000;
        npcMaxBid = 70000 + rand() % 80000; // NPC는 최대 7만~15만까지 부름 (영끌 배틀)
    }

    cout << "\n오늘의 출품작: " << itemName << " (능력치: +" << stat << ")" << endl;
    cout << "시작 입찰가: " << YELLOW << startingBid << " G" << RESET << endl;
    cout << "[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

    cout << "\n1. 경매에 참가한다  2. 돈이 없으니 얌전히 나간다\n선택: ";
    int choice;
    cin >> choice;

    if (choice != 1)
        return;

    int currentBid = startingBid;
    bool bidding = true;

    while (bidding)
    {
        cout << "\n----------------------------------------" << endl;
        cout << "현재 최고 입찰가: " << YELLOW << currentBid << " G" << RESET << endl;
        cout << "1. " << currentBid + 1000 << " G 부르기 (+1,000)" << endl;
        cout << "2. " << currentBid + 5000 << " G 부르기 (+5,000)" << endl;
        cout << "3. 경쟁자를 압도! " << currentBid + 20000 << " G 부르기 (+20,000)" << endl;
        cout << "4. 쫄아서 포기하기 (입찰 포기)\n선택: ";

        int bidChoice;
        cin >> bidChoice;
        int myBid = currentBid;

        if (bidChoice == 1)
            myBid += 1000;
        else if (bidChoice == 2)
            myBid += 5000;
        else if (bidChoice == 3)
            myBid += 20000;
        else
        {
            cout << RED << "\n경매사: 모험가님께서 입찰을 포기하셨습니다! 물건은 다른 귀족에게 넘어갑니다." << RESET << endl;
            break;
        }

        if (player.gold < myBid)
        {
            cout << RED << "골드가 부족하여 그 금액을 부를 수 없습니다!" << RESET << endl;
            continue;
        }

        currentBid = myBid;
        cout << GREEN << "\n당신: " << currentBid << " 골드!!" << RESET << endl;

        // NPC의 반격 로직
        if (currentBid >= npcMaxBid)
        {
            cout << CYAN << "경매장 안이 술렁입니다... 더 이상 입찰할 귀족이 없는 것 같군요!" << RESET << endl;
            cout << "경매사: " << YELLOW << currentBid << " 골드! 더 없습니까? ...낙찰입니다!!!" << RESET << endl;

            player.gold -= currentBid;
            player.inventory.push_back(Item(itemName, itemType, stat, currentBid / 2));

            cout << GREEN << "\n어마어마한 돈을 쏟아부어 [" << itemName << "]을(를) 손에 넣었습니다!" << RESET << endl;
            break;
        }
        else
        {
            int npcRaise = (rand() % 3 + 1) * 2000; // NPC가 2천~6천씩 쪼잔하게 올림
            currentBid += npcRaise;
            cout << RED << "오만한 귀족 NPC: 흥, 내가 " << currentBid << " 골드를 내겠소!" << RESET << endl;
        }
    }
    cout << "\n엔터를 누르면 마을 광장으로 돌아갑니다...";
    cin.ignore();
    cin.get();
}