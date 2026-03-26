#include "../include/Bank.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Bank::visit(Player &player)
{
    bool inBank = true;
    while (inBank)
    {
        system("cls");
        cout << CYAN << "\n=== 마을 은행 ===" << RESET << endl;
        cout << "은행장: 안전한 자산 관리! 던전을 돌파할 때마다 예금액에 3%의 복리 이자가 붙습니다." << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
        cout << "[ 예금 잔액 ]: " << GREEN << player.bankGold << " G" << RESET << endl;

        cout << "\n1. 입금하기" << endl;
        cout << "2. 출금하기" << endl;
        cout << "3. 은행 나가기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "입금할 금액을 입력하세요 (0. 취소): ";
            int amount;
            cin >> amount;
            if (amount > 0 && amount <= player.gold)
            {
                player.gold -= amount;
                player.bankGold += amount;
                cout << GREEN << amount << " G를 성공적으로 입금했습니다." << RESET << endl;
            }
            else if (amount != 0)
            {
                cout << RED << "잔액이 부족하거나 잘못된 금액입니다." << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "출금할 금액을 입력하세요 (0. 취소): ";
            int amount;
            cin >> amount;
            if (amount > 0 && amount <= player.bankGold)
            {
                player.bankGold -= amount;
                player.gold += amount;
                cout << YELLOW << amount << " G를 성공적으로 출금했습니다." << RESET << endl;
            }
            else if (amount != 0)
            {
                cout << RED << "예금 잔액이 부족하거나 잘못된 금액입니다." << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "은행을 나섭니다..." << endl;
            inBank = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inBank)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}