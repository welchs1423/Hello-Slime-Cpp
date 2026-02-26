#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h" // 우리가 만든 플레이어 설계도를 가져옴

using namespace std;

int main() {
    system("chcp 65001");
    srand(time(0)); 

    Player player; // 설계도를 바탕으로 실제 플레이어 객체 생성!

    cout << "=== 끝없는 슬라임 사냥터에 입장했습니다! ===" << endl;

    while (player.hp > 0) {
        int slimeHp = 30 + (player.level * 10); 
        cout << "\n=========================================" << endl;
        cout << "야생의 슬라임(HP: " << slimeHp << ")이 나타났다!" << endl;

        while (player.hp > 0 && slimeHp > 0) {
            player.printStatus(); // 상태 출력 함수 호출
            cout << "[슬라임] HP: " << slimeHp << endl;
            cout << "1. 공격하기  2. 도망가기  3. 물약 마시기(남은 개수: " << player.potions << ")\n선택: ";
            
            int choice;
            cin >> choice;

            if (choice == 1) {
                int damage = player.attack(); // 공격 함수 호출 후 데미지 받아오기
                slimeHp -= damage;

                if (slimeHp > 0) {
                    int slimeDamage = rand() % 5 + 5 + player.level; 
                    player.takeDamage(slimeDamage); // 피해 입는 함수 호출
                }
            } else if (choice == 2) {
                cout << "전투에서 도망쳤습니다... 사냥터를 빠져나갑니다." << endl;
                return 0; 
            } else if (choice == 3) {
                player.heal(); // 회복 함수 호출
            } else {
                cout << "잘못된 입력입니다." << endl;
            }
        }

        if (slimeHp <= 0) {
            cout << "\n🎉 슬라임을 물리쳤습니다!" << endl;
            player.gainExp(50); // 경험치 획득 함수 호출
        }
    }

    if (player.hp <= 0) cout << "\n 플레이어가 쓰러졌습니다... 눈앞이 깜깜해집니다. 게임 오버." << endl;
    
    return 0;
}