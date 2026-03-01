#include "Shop.h"
#include "Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Shop::visit(Player& player) {
    bool shopping = true;

    while (shopping) {
        system("cls");
        cout << CYAN << "\n=== 🛒 마을 상점 ===" << RESET << endl;
        player.printStatus();
        
        cout << "\n[ 회복 물약 ]" << endl;
        cout << "1. 체력 포션 (30G)" << endl;
        cout << "2. 마나 포션 (30G)" << endl;
        cout << "\n[ 무기 및 방어구 ]" << endl;
        cout << "3. 철검 (+10 ATK) (100G)" << endl;
        cout << "4. 강철검 (+25 ATK) (250G)" << endl;
        cout << "5. 가죽 갑옷 (+5 DEF) (80G)" << endl;
        cout << "6. 철 갑옷 (+15 DEF) (200G)" << endl;
        cout << "\n[ 대장간 & 기타 ]" << endl;
        cout << "7. 무기 강화 (+5 ATK) (50G)" << endl;
        cout << "8. 방어구 강화 (+3 DEF) (50G)" << endl;
        cout << "9. 🎁 미스터리 박스 (50G)" << endl;
        cout << "\n10. 상점 나가기\n선택: ";

        int shopChoice;
        cin >> shopChoice;

        system("cls");

        switch (shopChoice) {
            case 1:
                if (player.gold >= 30) {
                    player.gold -= 30; player.potions++;
                    // ✨ 가방에 진짜 포션 객체 추가! (이름, 타입(3:소모품), 회복량, 가격)
                    player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                    cout << GREEN << "체력 포션을 구매하여 가방에 넣었습니다! (보유량: " << player.potions << ")" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 2:
                if (player.gold >= 30) {
                    player.gold -= 30; player.manaPotions++;
                    player.inventory.push_back(Item("마나 포션", 3, 50, 30));
                    cout << CYAN << "마나 포션을 구매하여 가방에 넣었습니다! (보유량: " << player.manaPotions << ")" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 3:
                if (player.gold >= 100) {
                    player.gold -= 100; player.weaponDamage = 10;
                    // ✨ 가방에 진짜 무기 객체 추가! (이름, 타입(1:무기), 공격력, 가격)
                    player.inventory.push_back(Item("철검", 1, 10, 100));
                    cout << GREEN << "철검을 구매하여 장착하고, 가방에도 넣었습니다!" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 4:
                if (player.gold >= 250) {
                    player.gold -= 250; player.weaponDamage = 25;
                    player.inventory.push_back(Item("강철검", 1, 25, 250));
                    cout << GREEN << "강철검을 구매하여 장착하고, 가방에도 넣었습니다!" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 5:
                if (player.gold >= 80) {
                    player.gold -= 80; player.armorDefense = 5;
                    // ✨ 가방에 진짜 방어구 객체 추가! (이름, 타입(2:방어구), 방어력, 가격)
                    player.inventory.push_back(Item("가죽 갑옷", 2, 5, 80));
                    cout << GREEN << "가죽 갑옷을 구매하여 장착하고, 가방에도 넣었습니다!" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 6:
                if (player.gold >= 200) {
                    player.gold -= 200; player.armorDefense = 15;
                    player.inventory.push_back(Item("철 갑옷", 2, 15, 200));
                    cout << GREEN << "철 갑옷을 구매하여 장착하고, 가방에도 넣었습니다!" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 7:
                if (player.gold >= 50) {
                    player.gold -= 50; player.weaponLevel++;
                    cout << YELLOW << "🔨 깡! 깡! 무기가 강화되었습니다! (현재: +" << player.weaponLevel << ")" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 8:
                if (player.gold >= 50) {
                    player.gold -= 50; player.armorLevel++;
                    cout << YELLOW << "✨ 갑옷이 단단해졌습니다! (현재: +" << player.armorLevel << ")" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 9:
                if (player.gold >= 50) {
                    player.gold -= 50;
                    cout << YELLOW << "🎁 미스터리 박스를 엽니다..." << RESET << endl;
                    int roll = rand() % 100;
                    if (roll < 10) {
                        cout << YELLOW << "🎉 잭팟! 200 골드를 발견했습니다!" << RESET << endl;
                        player.gold += 200;
                    } else if (roll < 40) {
                        cout << GREEN << "✨ 체력 포션 2개와 마나 포션 1개를 얻었습니다! (가방에 추가됨)" << RESET << endl;
                        player.potions += 2; player.manaPotions += 1;
                        // 가챠 당첨 포션들도 가방에 넣어줍니다
                        player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                        player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                        player.inventory.push_back(Item("마나 포션", 3, 50, 30));
                    } else if (roll < 70) {
                        cout << CYAN << "🔨 신비한 망치가 무기를 내리칩니다! 무기 레벨 +1!" << RESET << endl;
                        player.weaponLevel++;
                    } else {
                        cout << RED << "😭 돌멩이뿐입니다... 쓸모없는 돌멩이를 가방에 챙겼습니다." << RESET << endl;
                        // ✨ 꽝에 당첨되면 인벤토리에 쓰레기를 넣어버립니다
                        player.inventory.push_back(Item("쓸모없는 돌멩이", 4, 0, 0));
                    }
                } else {
                    cout << RED << "골드가 부족합니다!" << RESET << endl;
                }
                break;
            case 10:
                cout << "상점을 나섭니다..." << endl;
                shopping = false; 
                break;
            default:
                cout << RED << "잘못된 입력입니다." << RESET << endl;
                break;
        }

        if (shopping) {
            cout << "\n엔터를 누르면 상점 메뉴로 돌아갑니다...";
            cin.ignore();
            cin.get();
        }
    }
}