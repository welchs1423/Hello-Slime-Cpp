#include "../include/Alchemy.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void Alchemy::visit(Player &player)
{
    bool inAlchemy = true;
    while (inAlchemy)
    {
        system("cls");
        cout << MAGENTA << "\n=== [ 고대의 연금술 공방 ] ===" << RESET << endl;
        cout << "연금술사: 흐흐... 버릴 물건이 있다면 이 가마솥에 다 집어넣어 보게. 황금이 될지, 잿더미가 될지는 모르지만!" << endl;

        cout << "\n1. 불필요한 장비 일괄 분해 (장비 -> 골드 연성)" << endl;
        cout << "2. 포션 융합 연성 (포션 3개 -> 낮은 확률로 영구 스탯 영약!)" << endl;
        cout << "3. 공방 나서기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << CYAN << "\n가마솥이 보글보글 끓어오릅니다..." << RESET << endl;
            int totalGoldGained = 0;
            vector<Item> keptItems;
            int dismantledCount = 0;

            // 가방을 뒤져서 장착 안 한 1성~3성 장비만 갈아버림
            for (auto &item : player.inventory)
            {
                // 타입 1(무기), 2(방어구) 이면서 장착 중이 아닌 것
                if ((item.type == 1 || item.type == 2) && !item.isEquipped)
                {
                    // 이름에 '신화'나 '영웅'이 안 들어간 것만 분해 (안전장치)
                    if (item.name.find("4성") == string::npos && item.name.find("5성") == string::npos && item.name.find("전설") == string::npos)
                    {
                        int goldValue = item.price / 2 + (rand() % 50); // 상점 판매가보다 살짝 높은 연성 효율
                        totalGoldGained += goldValue;
                        dismantledCount++;
                        continue; // keptItems에 넣지 않음 (삭제됨)
                    }
                }
                keptItems.push_back(item); // 분해 안 한 아이템은 유지
            }

            if (dismantledCount > 0)
            {
                player.inventory = keptItems; // 가방 업데이트
                player.gold += totalGoldGained;
                cout << GREEN << dismantledCount << "개의 장비를 분해하여 " << YELLOW << totalGoldGained << " G" << GREEN << " 로 연성했습니다!" << RESET << endl;
            }
            else
            {
                cout << RED << "분해할 만한 잉여 장비(1~3성 미장착)가 가방에 없습니다!" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            int potionCount = 0;
            vector<int> potionIndices;

            // 가방에서 포션(타입 3, 4) 개수 확인
            for (int i = 0; i < player.inventory.size(); ++i)
            {
                if (player.inventory[i].type == 3 || player.inventory[i].type == 4)
                {
                    potionCount++;
                    potionIndices.push_back(i);
                }
            }

            if (potionCount >= 3)
            {
                cout << YELLOW << "\n포션 3개를 가마솥에 던져 넣습니다..." << RESET << endl;

                // 뒤에서부터 포션 3개 삭제 (인덱스 꼬임 방지)
                for (int i = 2; i >= 0; --i)
                {
                    player.inventory.erase(player.inventory.begin() + potionIndices[i]);
                }

                int roll = rand() % 100;
                cout << CYAN << "퍼펑!! 매캐한 연기가 피어오릅니다..." << RESET << endl;

                if (roll < 10)
                { // 10% 대성공 (마법탑 5000G 짜리 영약)
                    cout << MAGENTA << "!!! 연성 대성공 !!! [세계수의 비약]이 탄생했습니다!" << RESET << endl;
                    cout << "마시자마자 영구적으로 최대 체력이 30 증가합니다!" << endl;
                    player.maxHp += 30;
                    player.hp += 30;
                }
                else if (roll < 50)
                { // 40% 성공
                    cout << GREEN << "빛나는 [특제 농축 포션]이 완성되었습니다! (HP/MP 100% 회복)" << RESET << endl;
                    player.hp = player.maxHp;
                    player.mp = player.maxMp;
                }
                else
                { // 50% 실패
                    cout << RED << "가마솥이 폭발했습니다! 시꺼먼 재만 남았습니다... (포션 증발)" << RESET << endl;
                }
            }
            else
            {
                cout << RED << "연성에 필요한 포션이 부족합니다! (최소 3개 필요, 현재: " << potionCount << "개)" << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "공방의 매캐한 연기를 뚫고 밖으로 나옵니다..." << endl;
            inAlchemy = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inAlchemy)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}