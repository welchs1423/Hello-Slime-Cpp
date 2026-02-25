#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){

    system("chcp 65001");
    
    int playerHp = 100;
    int slimeHp = 30;
    int potions = 3; // 물약 갯수

    srand(time(0));

    cout << "=== 야생의 슬라임과 조우했습니다! ===" << endl;

    while (playerHp > 0 && slimeHp > 0){
        cout << "\n[현재 상태] 플레이어 HP: " << playerHp << " / 슬라임 HP: " << slimeHp << endl;
        cout << "1. 공격하기  2. 도망가기  3. 물약 마시기(남은 개수: " << potions << ")\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int damage = rand() % 10 + 10;
            slimeHp -= damage;
            cout << "슬라임을 공격해서 " << damage << "의 피해를 입혔습니다!" << endl;
        } else if(choice == 2){
            cout << "무사히 도망쳤습니다..." << endl;
            break;
        } else if (choice == 3){
            if(potions > 0){
                playerHp += 30;
                if(playerHp > 100) playerHp = 100;
                potions--;
                cout << "물약을 마셨습니다! HP가 30 회복되었습니다. (남은 물약: )" << potions << ")" << endl;
            } else{
                cout << "물약이 없습니다!" << endl;
            }
        } else {
            cout << "잘못된 입력입니다." << endl;
        }
    }

    if(slimeHp <= 0) cout << "\n축하합니다! 슬라임을 물리쳤습니다!" << endl;
    return 0;
}