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
        
        // ✨ 매입 메뉴 추가!
        cout << "\n[ 매입 ]" << endl;
        cout << "10. 💰 내 아이템 팔기" << endl;
        cout << "\n11. 상점 나가기\n선택: ";

        int shopChoice;
        cin >> shopChoice;

        system("cls");

        switch (shopChoice) {
            case 1:
                if (player.gold >= 30) {
                    player.gold -= 30; player.potions++;
                    player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                    cout << GREEN << "체력 포션을 구매하여 가방에 넣었습니다! (보유량: " << player.potions << ")" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 2:
                if (player.gold >= 30) {
                    player.gold -= 30; player.manaPotions++;
                    player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                    cout << CYAN << "마나 포션을 구매하여 가방에 넣었습니다! (보유량: " << player.manaPotions << ")" << RESET << endl;
                } else cout << RED << "골드가 부족합니다!" << RESET << endl;
                break;
            case 3:
                if (player.gold >= 100) {
                    player.gold -= 100; player.weaponDamage = 10;
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
                        player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                        player.inventory.push_back(Item("체력 포션", 3, 50, 30));
                        player.inventory.push_back(Item("마나 포션", 4, 50, 30));
                    } else if (roll < 70) {
                        cout << CYAN << "🔨 신비한 망치가 무기를 내리칩니다! 무기 레벨 +1!" << RESET << endl;
                        player.weaponLevel++;
                    } else {
                        cout << RED << "😭 돌멩이뿐입니다... 쓸모없는 돌멩이를 가방에 챙겼습니다." << RESET << endl;
                        player.inventory.push_back(Item("쓸모없는 돌멩이", 5, 0, 0));
                    }
                } else {
                    cout << RED << "골드가 부족합니다!" << RESET << endl;
                }
                break;
            case 10: {
                // ✨ 아이템 판매 로직 시작!
                bool selling = true;
                while (selling) {
                    system("cls");
                    cout << YELLOW << "\n=== 💰 아이템 판매 ===" << RESET << endl;
                    cout << "상인: \"어떤 물건을 팔텐가? 매입가는 원가의 절반이라네!\"\n" << endl;
                    cout << "[ 현재 골드: " << player.gold << "G ]\n" << endl;

                    if (player.inventory.empty()) {
                        cout << "가방이 텅 비어있습니다." << endl;
                        cout << "\n엔터를 누르면 상점 메뉴로 돌아갑니다...";
                        cin.ignore(); cin.get();
                        break; // 판매 창 탈출
                    }

                    for (size_t i = 0; i < player.inventory.size(); i++) {
                        // 판매가는 원가의 50% (돌멩이는 1골드로 쳐줌)
                        int sellPrice = player.inventory[i].price / 2;
                        if (player.inventory[i].name == "쓸모없는 돌멩이") sellPrice = 1;

                        cout << i + 1 << ". ";
                        if (player.inventory[i].isEquipped) cout << GREEN << "[E] " << RESET;
                        
                        cout << "[" << player.inventory[i].getTypeName() << "] " 
                             << player.inventory[i].name << " (판매가: " << YELLOW << sellPrice << "G" << RESET << ")" << endl;
                    }

                    cout << "\n0. 판매 종료 (상점 메뉴로)\n팔고 싶은 아이템 번호를 입력하세요: ";
                    int sellChoice;
                    cin >> sellChoice;

                    if (sellChoice == 0) {
                        selling = false; 
                    } else if (sellChoice > 0 && sellChoice <= player.inventory.size()) {
                        int index = sellChoice - 1;
                        
                        // 장착 중인 아이템은 판매 불가!
                        if (player.inventory[index].isEquipped) {
                            cout << RED << "\n장착 중인 아이템은 팔 수 없습니다! 가방에서 장착 해제 후 팔아주세요." << RESET << endl;
                        } else {
                            int sellPrice = player.inventory[index].price / 2;
                            if (player.inventory[index].name == "쓸모없는 돌멩이") sellPrice = 1;
                            
                            cout << GREEN << "\n상인에게 [" << player.inventory[index].name << "]을(를) 팔고 " << sellPrice << "G를 받았습니다!" << RESET << endl;
                            
                            // 포션을 팔면 스탯 상의 포션 개수도 동기화해서 빼줌
                            if (player.inventory[index].type == 3 && player.potions > 0) player.potions--;
                            if (player.inventory[index].type == 4 && player.manaPotions > 0) player.manaPotions--;
                            
                            player.gold += sellPrice;
                            player.inventory.erase(player.inventory.begin() + index); // 가방에서 삭제
                        }
                        
                        cout << "엔터를 누르면 계속합니다...";
                        cin.ignore(); cin.get();
                    } else {
                        cout << RED << "잘못된 번호입니다." << RESET << endl;
                        cout << "엔터를 누르면 계속합니다...";
                        cin.ignore(); cin.get();
                    }
                }
                break; // case 10 끝
            }
            case 11:
                cout << "상점을 나섭니다..." << endl;
                shopping = false; 
                break;
            default:
                cout << RED << "잘못된 입력입니다." << RESET << endl;
                break;
        }

        // 10번(판매) 메뉴를 돌고 나왔을 때는 이미 일시정지를 했으므로 연속으로 엔터를 요구하지 않게 처리
        if (shopping && shopChoice != 10) {
            cout << "\n엔터를 누르면 상점 메뉴로 돌아갑니다...";
            cin.ignore();
            cin.get();
        }
    }
}