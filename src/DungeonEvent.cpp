#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// 이벤트가 발생했으면 true, 아무 일도 없었으면 false를 반환
bool DungeonEvent::triggerEvent(Player& player){
    int roll = rand() % 100;
    
    // 70% 확률로 몬스터 조우 (이벤트 발생 X)
    if(roll < 70){
        return false;
    }

    system("cls");
    cout << CYAN << "\n=== 던전 탐험 이벤트 ===" << RESET << endl;

    // 나머지 30% 확률 안에서 어떤 이벤트가 터질지 결정
    int eventType = rand() % 3;

    if(eventType == 0){
        // 독화살 함정
        int trapDamage = 15 + (player.dungeonFloor * 2);
        player.hp -= trapDamage;
        if (player.hp < 0) player.hp = 0;

        cout << RED << "앗! 발밑에서 '딸깍' 하는 소리가 들립니다..." << RESET << endl;
        cout << RED << "독화살 함정에 당했습니다! (-" << trapDamage << " HP)" << RESET << endl;
    } else if (eventType == 1){
        // 요정의 샘물
        int healAmount = 30 + (player.dungeonFloor * 5);
        player.hp += healAmount;
        if (player.hp > player.maxHp) player.hp = player.maxHp;

        player.mp += healAmount;
        if (player.mp > player.maxMp) player.mp = player.maxMp;

        cout << BLUE << "신비롭게 빛나는 요정의 샘물을 발견했습니다!" << RESET << endl;
        cout << GREEN << "달콤한 물을 마시고 체력과 마나가 회복되었습니다. (+ " << healAmount << ")" << RESET << endl;
    } else if(eventType == 2){
        // 버려진 보물상자
        int goldFound = 50 + (player.dungeonFloor * 10);
        player.gold += goldFound;

        cout << YELLOW << "구석에 먼지 쌓인 보물상자가 있습니다..." << RESET << endl;
        cout << YELLOW << "상자를 열어보니 " << goldFound << " 골드가 들어있습니다!" << RESET << endl;
    }

    cout << "\n엔터를 누르면 계속 탐험합니다...";
    cin.ignore();
    cin.get();

    // 이벤트로 인해 플레이어가 사망했는지 체크
    if(player.hp <= 0){
        cout << RED << "\n당신은 던전의 위험을 견디지 못하고 쓰러졌습니다..." << RESET << endl;
    }
    
    return true;
}