#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool DungeonEvent::triggerEvent(Player &player)
{
    int chance = rand() % 100;

    // 80% 확률로 이벤트 발생 안 함 (정상 전투 진행)
    if (chance >= 20)
        return false;

    system("cls");
    cout << CYAN << "\n==========================================" << RESET << endl;
    cout << YELLOW << "        [ 던전 랜덤 인카운터 발생! ]" << RESET << endl;
    cout << CYAN << "==========================================\n"
         << RESET << endl;

    int eventType = rand() % 3;

    if (eventType == 0)
    {
        cout << "기묘하게 빛나는 " << BLUE << "[요정의 샘]" << RESET << "을 발견했습니다." << endl;
        cout << "갈증이 심하게 납니다. 물을 마시겠습니까?" << endl;
        cout << "1. 물을 마신다 (도박)  2. 찜찜하니 지나친다\n선택: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (rand() % 2 == 0)
            {
                cout << GREEN << "\n달콤하고 시원한 물입니다! HP와 MP가 모두 회복되었습니다." << RESET << endl;
                player.hp = player.maxHp;
                player.mp = player.maxMp;
            }
            else
            {
                cout << RED << "\n썩은 물이었습니다! 심한 배탈이 나서 체력이 크게 감소합니다." << RESET << endl;
                player.hp -= (player.maxHp / 4);
                if (player.hp <= 0)
                    player.hp = 1; // 죽지는 않게 보정
            }
        }
        else
        {
            cout << "유혹을 뿌리치고 안전하게 발걸음을 옮깁니다." << endl;
        }
    }
    else if (eventType == 1)
    {
        cout << "던전 구석에서 " << GREEN << "[떠돌이 고블린 상인]" << RESET << "을 만났습니다." << endl;
        cout << "상인: \"키히힉! 좋은 물건이 있다구! 단돈 500G에 이 상자를 열어보게!\"" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
        cout << "1. 수상한 상자를 산다 (500G)  2. 무시하고 간다\n선택: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (player.gold >= 500)
            {
                player.gold -= 500;
                int gacha = rand() % 100;
                if (gacha < 20)
                {
                    cout << MAGENTA << "\n!!! 잭팟 !!! 상자 안에서 [찬란한 다이아몬드]가 나왔습니다!" << RESET << endl;
                    cout << "마을 상점에 비싸게 팔 수 있을 것 같습니다." << endl;
                    player.inventory.push_back(Item("찬란한 다이아몬드", 6, 0, 3000));
                }
                else if (gacha < 50)
                {
                    cout << CYAN << "\n상자 안에서 [마나 포션] 2개를 발견했습니다. 나쁘지 않네요." << RESET << endl;
                    player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                    player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                }
                else
                {
                    cout << RED << "\n상자 안에는 냄새나는 고블린 양말뿐이었습니다... 상인은 이미 도망쳤습니다." << RESET << endl;
                }
            }
            else
            {
                cout << RED << "\n상인: \"돈도 없는 빈털터리잖아! 퉤!\"" << RESET << endl;
            }
        }
        else
        {
            cout << "사기꾼의 냄새를 맡고 조용히 지나갑니다." << endl;
        }
    }
    else
    {
        cout << "오래된 " << MAGENTA << "[고대의 제단]" << RESET << "이 있습니다. 누군가 기도를 올린 흔적이 있습니다." << endl;
        cout << "제단에 무언가를 바치면 신의 축복을 받을지도 모릅니다." << endl;
        cout << "1. 300G를 바치고 기도한다  2. 제단을 발로 차서 부순다  3. 지나간다\n선택: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (player.gold >= 300)
            {
                player.gold -= 300;
                cout << CYAN << "\n신성한 기운이 몸을 감쌉니다! 영구적으로 최대 마나가 10 증가합니다!" << RESET << endl;
                player.maxMp += 10;
                player.mp += 10;
            }
            else
            {
                cout << RED << "\n바칠 돈이 부족하여 신이 응답하지 않습니다." << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            if (rand() % 100 < 30)
            {
                cout << YELLOW << "\n제단이 부서지며 숨겨져 있던 금화 500G가 쏟아져 나왔습니다!" << RESET << endl;
                player.gold += 500;
            }
            else
            {
                cout << RED << "\n제단을 부수자 벼락이 내리칩니다! 공격력이 영구적으로 1 감소합니다..." << RESET << endl;
                if (player.str > 1)
                    player.str -= 1;
            }
        }
        else
        {
            cout << "미신을 믿지 않는 당신은 쿨하게 지나갑니다." << endl;
        }
    }

    cout << "\n엔터를 누르면 전투 없이 다음 층으로 이동합니다...";
    cin.ignore();
    cin.get();
    return true; // 이벤트 발생 시 전투 스킵
}