#include "GameManager.h"
#include "Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

GameManager::GameManager() {
    isPlaying = true;
}

void GameManager::run() {
    system("cls");
    cout << CYAN << "=== Slime Hunter RPG ===" << RESET << endl;
    cout << "1. New Game  2. Continue\nSelect: ";
    int startChoice;
    cin >> startChoice;

    if (startChoice == 2) {
        player.load();
    }

    while (isPlaying && player.hp > 0) {
        system("cls");
        cout << "\n=== 🏡 Town Square ===" << endl;
        player.printStatus();
        cout << "1. Enter Dungeon  2. Visit Shop  3. Save Game  4. Quit Game\nSelect: ";
        int townChoice;
        cin >> townChoice;

        if (townChoice == 1) {
            battle.start(player); // ✨ 전투 부서로 플레이어를 보냄!
        } else if (townChoice == 2) {
            shop.visit(player);   // ✨ 상점 부서로 플레이어를 보냄!
        } else if (townChoice == 3) {
            system("cls");
            player.save();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        } else if (townChoice == 4) {
            system("cls");
            cout << "Quitting game..." << endl;
            isPlaying = false;
        } else {
            system("cls");
            cout << RED << "Invalid input." << RESET << endl;
        }
    }

    if (player.hp <= 0) cout << RED << "\n💀 The player has fallen... Game Over." << RESET << endl;
}