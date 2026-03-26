#include "../include/Shop.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Shop::visit(Player &player)
{
    bool shopping = true;

    while (shopping)
    {
        system("cls");
        cout << CYAN << "\n=== 마을 상점 ===" << RESET << endl;
        player.printStatus();
        cout << YELLOW << "[내구도 상태] 무기: " << player.weaponDurability << "/50 | 방어구: " << player.armorDurability << "/50" << RESET << endl;

        cout << "\n[ 회복 물약 ]" << endl;
        cout << "1. 체력 포션 (30G)" << endl;
        cout << "2. 마나 포션 (30G)" << endl;
        cout << "\n[ 무기 및 방어구 ]" << endl;
        cout << "3. 철검 (+10 ATK) (100G)" << endl;
        cout << "4. 강철검 (+25 ATK) (250G)" << endl;
        cout << "5. 가죽 갑옷 (+5 DEF) (80G)" << endl;
        cout << "6. 철 갑옷 (+15 DEF) (200G)" << endl;
        cout << "\n[ 대장간 & 기타 ]" << endl;
        cout << "7. 무기 강화 확률형 (50G)" << endl;
        cout << "8. 방어구 강화 (+3 DEF) (50G)" << endl;
        cout << "9. 미스터리 박스 (50G)" << endl;
        cout << "\n[ 스킬북 ]" << endl;
        cout << "10. 스킬북: 연속 베기 (물리) (150G)" << endl;
        cout << "11. 스킬북: 블리자드 (마법) (200G)" << endl;
        cout << "12. 스킬북: 응급 처치 (회복) (100G)" << endl;
        cout << "\n[ 매입 및 수리 ]" << endl;
        cout << "13. 내 아이템 팔기" << endl;
        cout << "14. 장착 장비 전체 수리 (100G)" << endl;
        cout << "\n15. 상점 나가기\n선택: ";

        int shopChoice;
        cin >> shopChoice;
        system("cls");

        switch (shopChoice)
        {
        case 1:
            if (player.gold >= 30)
            {
                player.gold -= 30;
                player.potions++;
                player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                cout << GREEN << "체력 포션을 구매했습니다!" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 2:
            if (player.gold >= 30)
            {
                player.gold -= 30;
                player.manaPotions++;
                player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                cout << CYAN << "마나 포션을 구매했습니다!" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 3:
            if (player.gold >= 100)
            {
                player.gold -= 100;
                player.weaponDamage = 10;
                player.inventory.push_back(Item("철검", 1, 10, 100));
                cout << GREEN << "철검을 장착했습니다!" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 4:
            if (player.gold >= 250)
            {
                player.gold -= 250;
                player.weaponDamage = 25;
                player.inventory.push_back(Item("강철검", 1, 25, 250));
                cout << GREEN << "강철검을 장착했습니다!" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 5:
            if (player.gold >= 80)
            {
                player.gold -= 80;
                player.armorDefense = 5;
                player.inventory.push_back(Item("가죽 갑옷", 2, 5, 80));
                cout << GREEN << "가죽 갑옷을 장착했습니다!" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 6:
            if (player.gold >= 200)
            {
                player.gold -= 200;
                player.armorDefense = 15;
                player.inventory.push_back(Item("철 갑옷", 2, 15, 200));
                cout << GREEN << "철 갑옷을 장착했습니다!" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 7:
        {
            if (player.gold < 50)
            {
                cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            }
            player.gold -= 50;
            int currentLevel = player.weaponLevel;
            int roll = rand() % 100;
            cout << "\n대장장이: 깡... 깡... 깡...!" << endl;

            if (currentLevel < 3)
            {
                player.weaponLevel++;
                cout << GREEN << "강화 성공! 무기 레벨이 +" << player.weaponLevel << "이(가) 되었습니다." << RESET << endl;
            }
            else if (currentLevel < 6)
            {
                if (roll < 60)
                {
                    player.weaponLevel++;
                    cout << GREEN << "강화 성공! 무기 레벨이 +" << player.weaponLevel << "이(가) 되었습니다." << RESET << endl;
                }
                else
                {
                    cout << YELLOW << "강화 실패... 무기는 무사합니다. (현재: +" << player.weaponLevel << ")" << RESET << endl;
                }
            }
            else
            {
                if (roll < 30)
                {
                    player.weaponLevel++;
                    cout << MAGENTA << "대성공! 무기 레벨이 +" << player.weaponLevel << "이(가) 되었습니다!" << RESET << endl;
                }
                else if (roll < 70)
                {
                    player.weaponLevel--;
                    cout << RED << "강화 실패! 무기 레벨이 하락했습니다... (현재: +" << player.weaponLevel << ")" << RESET << endl;
                }
                else
                {
                    player.weaponLevel = 0;
                    player.weaponDurability /= 2;
                    cout << RED << "파괴! 무기가 손상되어 레벨이 초기화되고 내구도가 반토막 났습니다!" << RESET << endl;
                }
            }
            break;
        }
        case 8:
            if (player.gold >= 50)
            {
                player.gold -= 50;
                player.armorLevel++;
                cout << YELLOW << "갑옷이 단단해졌습니다! (현재: +" << player.armorLevel << ")" << RESET << endl;
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 9:
            if (player.gold >= 50)
            {
                player.gold -= 50;
                cout << YELLOW << "미스터리 박스를 엽니다..." << RESET << endl;
                int roll = rand() % 100;
                if (roll < 10)
                {
                    player.gold += 200;
                    cout << YELLOW << "200 골드를 발견했습니다!" << RESET << endl;
                }
                else if (roll < 40)
                {
                    player.potions += 2;
                    player.manaPotions += 1;
                    cout << GREEN << "포션 세트를 얻었습니다!" << RESET << endl;
                }
                else if (roll < 70)
                {
                    player.weaponLevel++;
                    cout << CYAN << "무기 레벨 +1!" << RESET << endl;
                }
                else
                {
                    cout << RED << "쓸모없는 돌멩이뿐입니다." << RESET << endl;
                }
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        case 10:
        {
            if (player.gold >= 150)
            {
                bool hasSkill = false;
                for (const auto &s : player.skills)
                {
                    if (s.name == "연속 베기")
                        hasSkill = true;
                }
                if (hasSkill)
                    cout << RED << "이미 배운 스킬입니다!" << RESET << endl;
                else
                {
                    player.gold -= 150;
                    player.skills.push_back(Skill("연속 베기", 15, 30, 1));
                    cout << GREEN << "새로운 물리 스킬 [연속 베기]를 배웠습니다!" << RESET << endl;
                }
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        }
        case 11:
        {
            if (player.gold >= 200)
            {
                bool hasSkill = false;
                for (const auto &s : player.skills)
                {
                    if (s.name == "블리자드")
                        hasSkill = true;
                }
                if (hasSkill)
                    cout << RED << "이미 배운 스킬입니다!" << RESET << endl;
                else
                {
                    player.gold -= 200;
                    player.skills.push_back(Skill("블리자드", 30, 40, 2));
                    cout << GREEN << "새로운 마법 스킬 [블리자드]를 배웠습니다!" << RESET << endl;
                }
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        }
        case 12:
        {
            if (player.gold >= 100)
            {
                bool hasSkill = false;
                for (const auto &s : player.skills)
                {
                    if (s.name == "응급 처치")
                        hasSkill = true;
                }
                if (hasSkill)
                    cout << RED << "이미 배운 스킬입니다!" << RESET << endl;
                else
                {
                    player.gold -= 100;
                    player.skills.push_back(Skill("응급 처치", 20, 30, 3));
                    cout << GREEN << "새로운 회복 스킬 [응급 처치]를 배웠습니다!" << RESET << endl;
                }
            }
            else
                cout << RED << "골드가 부족합니다!" << RESET << endl;
            break;
        }
        case 13:
            cout << "아이템 판매 메뉴는 가방에서 확인하세요." << endl;
            break;
        case 14:
            if (player.gold >= 100)
            {
                if (player.weaponDurability >= 50 && player.armorDurability >= 50)
                {
                    cout << YELLOW << "대장장이: 장비가 이미 완벽한 상태구만!" << RESET << endl;
                }
                else
                {
                    player.gold -= 100;
                    player.weaponDurability = 50;
                    player.armorDurability = 50;
                    cout << GREEN << "대장장이: 모든 장비의 내구도를 완벽하게 수리했네!" << RESET << endl;
                }
            }
            else
                cout << RED << "골드가 부족합니다! (필요: 100G)" << RESET << endl;
            break;
        case 15:
            cout << "상점을 나섭니다..." << endl;
            shopping = false;
            break;
        default:
            cout << RED << "잘못된 입력입니다." << RESET << endl;
            break;
        }

        if (shopping)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}