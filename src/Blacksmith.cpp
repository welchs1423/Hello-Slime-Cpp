#include "../include/Blacksmith.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Blacksmith::visit(Player &player)
{
    bool inForge = true;
    while (inForge)
    {
        system("cls");
        cout << RED << "\n=== [ 드워프의 대장간 ] ===" << RESET << endl;
        cout << "대장장이: 쇳물보다 뜨거운 열정만 있다면 뭐든 두들겨 주지! (+3까지는 안전, 이후는 파괴될 수도 있다고!)" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
        cout << "[ 현재 무기 ]: +" << player.weaponLevel << " (강화 시 공격력 +5)" << endl;
        cout << "[ 현재 방어구 ]: +" << player.armorLevel << " (강화 시 방어력 +3)" << endl;

        cout << "\n1. 무기 강화 하기" << endl;
        cout << "2. 방어구 강화 하기" << endl;
        cout << "3. 대장간 나가기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1 || choice == 2)
        {
            bool isWeapon = (choice == 1);
            int currentLevel = isWeapon ? player.weaponLevel : player.armorLevel;
            int cost = 100 + (currentLevel * 50); // 레벨이 높을수록 비싸짐

            cout << "\n현재 [+" << currentLevel << "] -> [+" << currentLevel + 1 << "] 강화 시도" << endl;
            cout << "필요 골드: " << YELLOW << cost << " G" << RESET << endl;
            cout << "진행하시겠습니까? (1. 예 / 2. 아니오): ";
            int confirm;
            cin >> confirm;

            if (confirm == 1)
            {
                if (player.gold < cost)
                {
                    cout << RED << "돈이 부족하잖아! 장사 접을 셈이야?" << RESET << endl;
                }
                else
                {
                    player.gold -= cost;
                    int roll = rand() % 100;
                    cout << CYAN << "\n깡! 깡! 깡! ..." << RESET << endl;

                    // 강화 확률 로직
                    if (currentLevel < 3)
                    {
                        cout << GREEN << "강화 성공! 안전하게 강화되었습니다." << RESET << endl;
                        if (isWeapon)
                            player.weaponLevel++;
                        else
                            player.armorLevel++;
                    }
                    else if (currentLevel < 6)
                    {
                        if (roll < 60)
                        {
                            cout << GREEN << "강화 성공! 장비가 더욱 단단해졌습니다!" << RESET << endl;
                            if (isWeapon)
                                player.weaponLevel++;
                            else
                                player.armorLevel++;
                        }
                        else
                        {
                            cout << RED << "강화 실패! 하지만 다행히 장비는 무사합니다." << RESET << endl;
                        }
                    }
                    else
                    { // +6 이상부터는 하락 및 초기화 위험 (도파민 구간)
                        if (roll < 30)
                        {
                            cout << MAGENTA << "!!! 대성공 !!! 엄청난 기운이 장비에 깃듭니다!" << RESET << endl;
                            if (isWeapon)
                                player.weaponLevel++;
                            else
                                player.armorLevel++;
                        }
                        else if (roll < 70)
                        {
                            cout << RED << "강화 실패... 장비의 등급이 1 하락했습니다." << RESET << endl;
                            if (isWeapon)
                                player.weaponLevel--;
                            else
                                player.armorLevel--;
                        }
                        else
                        {
                            cout << RED << "\n쩌적... 쨍그랑!" << RESET << endl;
                            cout << MAGENTA << "장비가 강화의 힘을 버티지 못하고 산산조각 났습니다! (수치 초기화)" << RESET << endl;
                            if (isWeapon)
                                player.weaponLevel = 0;
                            else
                                player.armorLevel = 0;
                        }
                    }
                }
            }
        }
        else if (choice == 3)
        {
            cout << "대장간을 나섭니다..." << endl;
            inForge = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inForge)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}