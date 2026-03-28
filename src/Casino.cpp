#include "../include/Casino.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Casino::visit(Player& player) {
    bool inCasino = true;
    while (inCasino) {
        system("cls");
        cout << YELLOW << "\n==================================================" << RESET << endl;
        cout << MAGENTA << "       ★★★ [ 제국 황립 카지노 (VIP 전용) ] ★★★" << RESET << endl;
        cout << YELLOW << "==================================================\n" << RESET << endl;
        cout << "딜러: 어서 오십시오, VIP님. 오늘 밤, 당신의 운을 시험해 보시겠습니까?" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
        
        cout << "\n1. 매직 슬롯 머신 (1회 1,000 G) - [ 7-7-7 잭팟: 100배! ]" << endl;
        cout << "2. 데스 다이스 (주사위 홀짝) - [ 승리 시 2배! ]" << endl;
        cout << "3. 카지노 나가기\n선택: ";
        
        int choice; cin >> choice;
        
        if (choice == 1) { // 슬롯 머신
            if (player.gold >= 1000) {
                player.gold -= 1000;
                cout << CYAN << "\n철칵... 띠리리리리링~!!!" << RESET << endl;
                
                int s1 = rand() % 9 + 1;
                int s2 = rand() % 9 + 1;
                int s3 = rand() % 9 + 1;
                
                cout << YELLOW << "\n[ " << s1 << " ] - [ " << s2 << " ] - [ " << s3 << " ]" << RESET << endl;
                
                if (s1 == 7 && s2 == 7 && s3 == 7) {
                    cout << MAGENTA << "\n!!! J A C K P O T !!!" << RESET << endl;
                    cout << YELLOW << "기적이 일어났습니다! 7-7-7 잭팟! 100,000 골드를 획득합니다!!!" << RESET << endl;
                    player.gold += 100000;
                } 
                else if (s1 == s2 && s2 == s3) {
                    cout << GREEN << "\n축하합니다! 트리플(" << s1 << ") 달성! 10,000 골드를 획득합니다!" << RESET << endl;
                    player.gold += 10000;
                } 
                else if (s1 == 7 || s2 == 7 || s3 == 7) {
                    cout << CYAN << "\n럭키 세븐(7)이 포함되어 참가상 500 골드를 돌려받습니다." << RESET << endl;
                    player.gold += 500;
                } 
                else {
                    cout << RED << "\n아쉽습니다. 꽝입니다! 기계가 당신의 돈을 집어삼켰습니다." << RESET << endl;
                }
            } else { cout << RED << "\n딜러: 1,000 골드도 없으면서 슬롯을 당기려 하시다니요. 쫓겨나고 싶습니까?" << RESET << endl; }
        } 
        else if (choice == 2) { // 주사위 홀/짝
            cout << "\n딜러: 두 개의 주사위를 굴려 합이 홀수일지 짝수일지 맞히시면 됩니다." << endl;
            cout << "베팅할 금액을 입력하세요: ";
            int bet; cin >> bet;
            
            if (bet > 0 && player.gold >= bet) {
                cout << "1. 홀수 (Odd)   2. 짝수 (Even)\n선택: ";
                int betChoice; cin >> betChoice;
                
                if (betChoice == 1 || betChoice == 2) {
                    player.gold -= bet;
                    cout << CYAN << "\n주사위가 구릅니다... 달그락! 달그락!" << RESET << endl;
                    
                    int d1 = rand() % 6 + 1;
                    int d2 = rand() % 6 + 1;
                    int sum = d1 + d2;
                    bool isEven = (sum % 2 == 0);
                    
                    cout << YELLOW << "주사위 결과: [ " << d1 << " ] + [ " << d2 << " ] = " << sum << RESET << endl;
                    
                    if ((betChoice == 1 && !isEven) || (betChoice == 2 && isEven)) {
                        cout << GREEN << "\n정답입니다! 베팅 금액의 2배(" << bet * 2 << " G)를 획득하셨습니다!" << RESET << endl;
                        player.gold += (bet * 2);
                    } else {
                        cout << RED << "\n틀렸습니다... 베팅한 골드는 카지노가 가져갑니다." << RESET << endl;
                    }
                } else { cout << RED << "잘못된 선택입니다. 베팅이 취소됩니다." << RESET << endl; }
            } else { cout << RED << "딜러: 장난치지 마십시오. 가진 돈 한도 내에서만 베팅할 수 있습니다." << RESET << endl; }
        }
        else if (choice == 3) {
            cout << "화려한 네온사인을 뒤로하고 카지노를 나섭니다..." << endl;
            inCasino = false;
        }
        else { cout << RED << "잘못된 입력입니다." << RESET << endl; }
        
        if (inCasino) {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore(); cin.get();
        }
    }
}