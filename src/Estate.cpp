#include "../include/Estate.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Estate::visit(Player &player)
{
    bool inEstate = true;
    while (inEstate)
    {
        system("cls");
        cout << GREEN << "\n=== [ 개인 영지 관리소 ] ===" << RESET << endl;

        if (player.hasEstate == false)
        {
            cout << "부동산 중개인: 오, 모험가님! 마침 마을 외곽에 아주 좋은 저택이 매물로 나왔습니다." << endl;
            cout << "부동산 중개인: 단돈 " << YELLOW << "20,000 G" << RESET << "면 이 저택의 주인이 되실 수 있죠!" << endl;
            cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
            cout << "1. 저택을 구매한다 (20,000 G)  2. 너무 비싸다... 돌아간다\n선택: ";

            int choice;
            cin >> choice;
            if (choice == 1)
            {
                if (player.gold >= 20000)
                {
                    player.gold -= 20000;
                    player.hasEstate = true; // Player 클래스에 이 변수가 없다면 새로 만들거나, 임시로 저장 없이 세션에만 적용해도 무방합니다.
                    cout << CYAN << "\n계약서에 서명했습니다! 이제 이 웅장한 저택은 당신의 것입니다!" << RESET << endl;
                    cout << "\n엔터를 눌러 내 집으로 입장합니다...";
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << RED << "\n중개인: 에잉, 돈도 모자라면서 사람을 불렀습니까!" << RESET << endl;
                    inEstate = false;
                }
            }
            else
            {
                inEstate = false;
            }
        }
        else
        {
            // 이미 집을 소유한 경우
            cout << "집사: 주인님, 환영합니다. 영지 관리를 도와드리겠습니다." << endl;
            cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
            cout << "\n1. 최고급 침대에서 휴식 (무료 - HP/MP 100% 회복)" << endl;
            cout << "2. 영지 훈련장 증축 (10,000 G - 영구 공격력 +3)" << endl;
            cout << "3. 영지 명상실 증축 (10,000 G - 영구 마력 +3)" << endl;
            cout << "4. 영지 밖으로 나가기\n선택: ";

            int eChoice;
            cin >> eChoice;
            if (eChoice == 1)
            {
                player.hp = player.maxHp;
                player.mp = player.maxMp;
                cout << GREEN << "폭신한 침대에서 무료로 푹 쉬었습니다! 컨디션 100%!" << RESET << endl;
            }
            else if (eChoice == 2)
            {
                if (player.gold >= 10000)
                {
                    player.gold -= 10000;
                    player.str += 3;
                    cout << RED << "마당에 훈련장을 짓고 피나는 수련을 했습니다! (영구 STR +3)" << RESET << endl;
                }
                else
                    cout << RED << "골드가 부족합니다!" << RESET << endl;
            }
            else if (eChoice == 3)
            {
                if (player.gold >= 10000)
                {
                    player.gold -= 10000;
                    player.intel += 3;
                    cout << CYAN << "조용한 명상실에서 마력을 가다듬습니다! (영구 INT +3)" << RESET << endl;
                }
                else
                    cout << RED << "골드가 부족합니다!" << RESET << endl;
            }
            else if (eChoice == 4)
            {
                cout << "대문을 나서 마을로 향합니다..." << endl;
                inEstate = false;
            }
            else
            {
                cout << RED << "잘못된 입력입니다." << RESET << endl;
            }
        }

        if (inEstate)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}