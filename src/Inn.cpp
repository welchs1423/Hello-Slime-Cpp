#include "../include/Inn.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Inn::visit(Player &player)
{
    bool resting = true;

    while (resting)
    {
        system("cls");
        cout << CYAN << "\n=== 마을 여관 ===" << RESET << endl;

        int discount = (player.innkeeperAffinity / 10) * 5;
        if (discount > 20)
            discount = 20;
        int cost = 30 - discount;

        cout << YELLOW << "여관 주인 호감도: " << player.innkeeperAffinity << " (숙박비 할인: " << discount << "G)" << RESET << endl;
        cout << "여관 주인: 어서오게! 편안한 방이 준비되어 있다네." << endl;
        cout << "\n[ 현재 체력: " << GREEN << player.hp << "/" << player.maxHp << RESET
             << " | 마나: " << CYAN << player.mp << "/" << player.maxMp << RESET
             << " | 골드: " << YELLOW << player.gold << "G" << RESET << " ]" << endl;

        cout << "\n1. 하룻밤 묵기 (" << cost << "G)" << endl;
        cout << "2. 주인장에게 팁 10G 건네기 (호감도 상승)" << endl;
        cout << "3. 여관 나가기\n선택: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (player.hp == player.maxHp && player.mp == player.maxMp)
            {
                cout << "이미 체력과 마나가 가득 차 있습니다!" << endl;
            }
            else if (player.gold >= cost)
            {
                player.gold -= cost;
                player.heal();
                player.restoreMp();
                cout << GREEN << cost << " 골드를 지불하고 푹 쉬었습니다. 체력과 마나가 모두 회복되었습니다!" << RESET << endl;
            }
            else
            {
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            }
            break;
        case 2:
            if (player.gold >= 10)
            {
                player.gold -= 10;
                player.innkeeperAffinity += 5;
                cout << YELLOW << "주인장: 오, 고맙네! 자네 정말 좋은 사람이구만!" << RESET << endl;
                cout << "여관 주인 호감도가 5 상승했습니다." << endl;
            }
            else
            {
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            }
            break;
        case 3:
            cout << "여관을 나섭니다..." << endl;
            resting = false;
            break;
        default:
            cout << RED << "잘못된 입력입니다." << RESET << endl;
            break;
        }

        if (resting)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}