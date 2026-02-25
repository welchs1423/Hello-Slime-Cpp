#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    system("chcp 65001"); // 한글 깨짐 방지

    // 플레이어 스탯 추가 (레벨, 경험치, 최대 체력)
    int playerLevel = 1;
    int playerExp = 0;
    int playerMaxHp = 100;
    int playerHp = playerMaxHp;
    int potions = 3;
    
    srand(time(0)); 

    cout << "=== 끝없는 슬라임 사냥터에 입장했습니다! ===" << endl;

    // 1. 외부 루프: 플레이어가 살아있는 한 계속 새로운 슬라임 등장
    while (playerHp > 0) {
        // 슬라임도 플레이어 레벨에 맞춰 조금씩 강해집니다
        int slimeHp = 30 + (playerLevel * 10); 
        cout << "\n=========================================" << endl;
        cout << "야생의 슬라임(HP: " << slimeHp << ")이 나타났다!" << endl;

        // 2. 내부 루프: 현재 슬라임과의 전투
        while (playerHp > 0 && slimeHp > 0) {
            cout << "\n[Lv." << playerLevel << " 플레이어] HP: " << playerHp << "/" << playerMaxHp << " | EXP: " << playerExp << "/100" << endl;
            cout << "[슬라임] HP: " << slimeHp << endl;
            cout << "1. 공격하기  2. 도망가기  3. 물약 마시기(남은 개수: " << potions << ")\n선택: ";
            
            int choice;
            cin >> choice;

            if (choice == 1) {
                // 레벨이 오를수록 기본 데미지도 증가
                int damage = rand() % 10 + 10 + (playerLevel * 2); 
                int critChance = rand() % 100;

                if (critChance < 20) {
                    damage *= 2;
                    cout << "⚡ 크리티컬 히트!! 슬라임의 급소를 찔러 " << damage << "의 피해를 입혔습니다!" << endl;
                } else {
                    cout << "슬라임을 공격해서 " << damage << "의 피해를 입혔습니다." << endl;
                }
                
                slimeHp -= damage;

                if (slimeHp > 0) {
                    int slimeDamage = rand() % 5 + 5 + playerLevel; 
                    playerHp -= slimeDamage;
                    cout << "슬라임의 반격! " << slimeDamage << "의 피해를 입었습니다." << endl;
                }
            } else if (choice == 2) {
                cout << "전투에서 도망쳤습니다... 사냥터를 빠져나갑니다." << endl;
                return 0; // 게임 완전 종료
            } else if (choice == 3) {
                if (potions > 0) {
                    playerHp += 30;
                    if (playerHp > playerMaxHp) playerHp = playerMaxHp;
                    potions--;
                    cout << "물약을 마셨습니다! HP가 회복되었습니다. (남은 물약: " << potions << ")" << endl;
                } else {
                    cout << "물약이 없습니다!" << endl;
                }
            } else {
                cout << "잘못된 입력입니다." << endl;
            }
        }

        // 슬라임을 잡았을 때의 보상 처리
        if (slimeHp <= 0) {
            cout << "\n🎉 슬라임을 물리쳤습니다!" << endl;
            playerExp += 50; // 슬라임 1마리당 경험치 50
            cout << "경험치를 50 획득했습니다." << endl;

            // 레벨업 조건 확인 (경험치 100 이상)
            if (playerExp >= 100) {
                playerLevel++;
                playerExp -= 100; // 남은 경험치 이월
                playerMaxHp += 20; // 최대 체력 증가
                playerHp = playerMaxHp; // 체력 풀 회복 보너스
                potions++; // 물약 1개 추가 보너스
                cout << "✨ 레벨 업! Lv." << playerLevel << "이 되었습니다! (최대 체력 증가, HP 모두 회복, 물약 1개 획득)" << endl;
            }
        }
    }

    if (playerHp <= 0) cout << "\n💀 플레이어가 쓰러졌습니다... 눈앞이 깜깜해집니다. 게임 오버." << endl;
    
    return 0;
}