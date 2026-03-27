#include "../include/MagicTower.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void MagicTower::visit(Player &player)
{
    bool inTower = true;
    while (inTower)
    {
        system("cls");
        cout << MAGENTA << "\n=== [ 신비한 마법탑 ] ===" << RESET << endl;
        cout << "대마법사: 진리를 탐구하는 자여... 묵직한 금화만 있다면 기적을 보여주지." << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

        cout << "\n1. 궁극기 마법서 열람" << endl;
        cout << "2. 고대의 영약(Elixir) 구매 (영구 스탯 증가)" << endl;
        cout << "3. 마법탑 나서기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << CYAN << "\n[ 궁극기 마법서 목록 ]" << RESET << endl;
            cout << "1. 헬파이어 (3000G / MP 50) - 적에게 엄청난 마법 폭발 데미지!" << endl;
            cout << "2. 홀리 라이트 (2500G / MP 40) - 자신의 체력을 대폭 회복!" << endl;
            cout << "0. 취소\n선택: ";
            int sChoice;
            cin >> sChoice;

            if (sChoice == 1 && player.gold >= 3000)
            {
                player.gold -= 3000;
                player.skills.push_back(Skill("헬파이어", 50, 100, 2)); // type 2: 마법 데미지
                cout << GREEN << "궁극기 [헬파이어]를 습득했습니다! 이제 던전을 불태우세요!" << RESET << endl;
            }
            else if (sChoice == 2 && player.gold >= 2500)
            {
                player.gold -= 2500;
                player.skills.push_back(Skill("홀리 라이트", 40, 100, 3)); // type 3: 회복
                cout << GREEN << "궁극기 [홀리 라이트]를 습득했습니다! 생존력이 극대화됩니다!" << RESET << endl;
            }
            else if (sChoice != 0)
            {
                cout << RED << "돈이 부족하거나 잘못된 입력이네!" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            cout << YELLOW << "\n[ 고대의 영약(Elixir) 목록 ] - 각 5000G (매우 비쌈!)" << RESET << endl;
            cout << "1. 거인의 비약 (영구 STR +5)" << endl;
            cout << "2. 현자의 비약 (영구 INT +5)" << endl;
            cout << "3. 세계수의 비약 (영구 MAX HP +50)" << endl;
            cout << "0. 취소\n선택: ";
            int eChoice;
            cin >> eChoice;

            if (eChoice >= 1 && eChoice <= 3 && player.gold >= 5000)
            {
                player.gold -= 5000;
                if (eChoice == 1)
                {
                    player.str += 5;
                    cout << GREEN << "근육이 팽창합니다! (영구 STR +5)" << RESET << endl;
                }
                else if (eChoice == 2)
                {
                    player.intel += 5;
                    cout << CYAN << "우주의 진리를 깨달았습니다! (영구 INT +5)" << RESET << endl;
                }
                else if (eChoice == 3)
                {
                    player.maxHp += 50;
                    player.hp += 50;
                    cout << RED << "엄청난 생명력이 넘쳐흐릅니다! (영구 MAX HP +50)" << RESET << endl;
                }
            }
            else if (eChoice != 0)
            {
                cout << RED << "어허! 영약은 아무나 먹는 게 아니야. 돈을 더 모아오게!" << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "마법탑을 나섭니다..." << endl;
            inTower = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inTower)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}