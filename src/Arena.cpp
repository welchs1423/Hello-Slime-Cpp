#include "../include/Arena.h"
#include "../include/MonsterFactory.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>
#include <memory>

using namespace std;

void Arena::visit(Player &player)
{
    system("cls");
    cout << RED << "\n=== [ 피의 투기장 (Colosseum) ] ===" << RESET << endl;
    cout << "투기장 마스터: 목숨을 걸고 한계를 시험해 볼 텐가? 승리할수록 상금은 기하급수적으로 늘어나지!" << endl;
    cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;
    cout << "입장료: 500 G" << endl;

    if (player.gold < 500)
    {
        cout << RED << "마스터: 돈도 없는 녀석이 어디서 기웃거려! 썩 꺼져라!" << RESET << endl;
        cout << "\n엔터를 누르면 돌아갑니다...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n1. 입장한다 (500 G 지불)  2. 쫄아서 도망친다\n선택: ";
    int choice;
    cin >> choice;
    if (choice != 1)
        return;

    player.gold -= 500;
    int wave = 1;
    int accumulatedGold = 0;
    bool inArena = true;

    while (inArena && player.hp > 0)
    {
        system("cls");
        cout << MAGENTA << "\n===================================" << RESET << endl;
        cout << RED << "        [ WAVE " << wave << " ] 전투 시작!" << RESET << endl;
        cout << MAGENTA << "===================================\n"
             << RESET << endl;

        // 투기장 전용 몬스터 스폰 (웨이브가 높아질수록 급격히 강해짐)
        unique_ptr<Monster> enemy(MonsterFactory::spawnMonster(wave * 4, player.level));
        enemy->hp = (int)(enemy->hp * 1.3f);
        enemy->maxHp = enemy->hp;
        enemy->atk = (int)(enemy->atk * 1.3f);

        if (wave % 5 == 0)
        {
            cout << RED << "!!! 보스 챔피언 등장 !!!" << RESET << endl;
            enemy->name = "투기장 챔피언 " + enemy->name;
            enemy->hp *= 2;
            enemy->maxHp = enemy->hp;
            enemy->atk = (int)(enemy->atk * 1.5f);
        }

        cout << RED << enemy->name << RESET << " (이)가 맹렬하게 달려듭니다!" << endl;

        bool inCombat = true;
        while (inCombat && player.hp > 0 && enemy->hp > 0)
        {
            cout << "\n[플레이어] HP: " << GREEN << player.hp << "/" << player.maxHp << RESET
                 << " | MP: " << CYAN << player.mp << "/" << player.maxMp << RESET << endl;
            cout << "[" << RED << enemy->name << RESET << "] HP: " << enemy->hp << "/" << enemy->maxHp << endl;

            cout << "1. 공격  2. 가방 (스킬/도망 불가! 오직 피지컬 승부!)\n선택: ";
            int bChoice;
            cin >> bChoice;
            system("cls");

            if (bChoice == 1)
            {
                int dmg = player.attack();
                if (rand() % 100 < 20)
                {
                    dmg = (int)(dmg * 1.5);
                    cout << YELLOW << "크리티컬 콤보!" << RESET << endl;
                }
                enemy->takeDamage(dmg);
                cout << YELLOW << dmg << "의 피해를 입혔습니다!" << RESET << endl;
            }
            else if (bChoice == 2)
            {
                player.openInventory();
            }
            else
            {
                cout << "잘못된 입력입니다." << endl;
            }

            if (enemy->hp > 0)
            {
                cout << "\n--- 적의 턴 ---" << endl;
                enemy->takeAction(player); // 몬스터 지능형 AI 연동
            }
        }

        // 결과 처리
        if (player.hp <= 0)
        {
            cout << RED << "\n투기장 바닥에 쓰러졌습니다... 마스터가 당신을 밖으로 던져버립니다!" << RESET << endl;
            cout << MAGENTA << "모든 누적 상금(" << accumulatedGold << " G)을 잃었습니다!" << RESET << endl;
            player.hp = 1; // 죽지는 않고 1의 체력으로 마을 귀환
            inArena = false;
        }
        else
        {
            // 상금 계산: 웨이브가 오를수록 기하급수적 증가
            int prize = (wave * 300) + (rand() % 200);
            if (wave % 5 == 0)
                prize *= 2; // 보스 웨이브는 2배
            accumulatedGold += prize;

            cout << YELLOW << "\nWave " << wave << " 클리어! (현재 누적 상금: " << accumulatedGold << " G)" << RESET << endl;
            cout << "\n투기장 마스터: 대단하군! 하지만 여기서 만족할 텐가?" << endl;
            cout << RED << "[주의: 다음 웨이브에서 죽으면 상금은 0원이 됩니다]" << RESET << endl;
            cout << "1. 다음 웨이브 도전 (Go)  2. 상금 챙겨서 나가기 (Stop)\n선택: ";

            int nextChoice;
            cin >> nextChoice;
            if (nextChoice == 2)
            {
                player.gold += accumulatedGold;
                cout << GREEN << "\n박수갈채를 받으며 투기장을 나섭니다! (" << accumulatedGold << " G 획득!)" << RESET << endl;
                inArena = false;
            }
            else
            {
                wave++;
            }
        }
    }
    if (player.hp > 0)
    {
        cout << "\n엔터를 누르면 마을 광장으로 돌아갑니다...";
        cin.ignore();
        cin.get();
    }
}