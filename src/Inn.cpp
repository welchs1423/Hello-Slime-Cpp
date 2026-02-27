#include "../include/Inn.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Inn::visit(Player& player){
    system("cls");
    cout << BLUE << "\n=== 마을 여관 ===" << RESET << endl;
    cout << "따뜻한 모닥불과 푹신한 침대가 있습니다." << endl;
    cout << "-> 1밤 묵어가기 (비용 30G, HP/MP 100% 회복)" << endl;
    cout << "\n 1. 결제하고 쉰다 \n 2. 그냥 나간다\n선택: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        if (player.gold >= 30){
            player.gold -= 30;
            player.hp = player.maxHp;
            player.mp = player.maxMp;
            cout << GREEN << "\n 푹 쉬고 일어났습니다! 체력과 마나가 모두 회복되었습니다." << RESET << endl;
        } else {
            cout << RED << "\n 골드가 부족합니다. 여관 주인이 매몰차게 쫓아냈습니다..." << RESET << endl;
        }
    } else {
        cout << "\n여관을 나섭니다." << endl;
    }

    cout << "\n엔터를 누르면 마을로 돌아갑니다...";
    cin.ignore();
    cin.get();
}