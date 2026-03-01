#include "GameManager.h"
#include "Colors.h"
#include "../include/Inn.h"
#include "../include/Guild.h"
#include <iostream>
#include <cstdlib>

using namespace std;

GameManager::GameManager() { isPlaying = true; }

void GameManager::run() {
    system("cls");
    cout << CYAN << "=== 슬라임 헌터 RPG ===" << RESET << endl;
    cout << "1. 새로 하기  2. 이어 하기\n선택: ";
    int startChoice; cin >> startChoice;

    if (startChoice == 1) player.chooseClass();
    else if (startChoice == 2) player.load();

    while (isPlaying && player.hp > 0) {
        system("cls");
        cout << "\n=== 🏡 마을 광장 ===" << endl;
        player.printStatus();
        
        // ✨ 6번 스탯 분배 추가!
        cout << "1. 던전 입장  2. 상점 방문  3. 여관 휴식 (30G)  4. 모험가 길드  5. 가방 열기  6. 🌟 스탯 분배  7. 게임 저장  8. 게임 종료\n선택: ";
        
        int townChoice; cin >> townChoice;

        if (townChoice == 1) battle.start(player); 
        else if (townChoice == 2) shop.visit(player);   
        else if (townChoice == 3) Inn::visit(player);   
        else if (townChoice == 4) Guild::visit(player);
        else if (townChoice == 5) player.openInventory(); 
        else if (townChoice == 6) player.allocateStats(); // ✨ 스탯 분배 실행!
        else if (townChoice == 7) {
            system("cls"); player.save();
            cout << "\n엔터를 누르면 계속합니다..."; cin.ignore(); cin.get();
        } 
        else if (townChoice == 8) {
            system("cls"); cout << "게임을 종료합니다..." << endl; isPlaying = false;
        } 
        else {
            system("cls"); cout << RED << "잘못된 입력입니다." << RESET << endl;
        }
    }
    if (player.hp <= 0) cout << RED << "\n💀 플레이어가 쓰러졌습니다... 게임 오버." << RESET << endl;
}