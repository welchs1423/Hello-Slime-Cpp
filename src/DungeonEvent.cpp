#include "../include/DungeonEvent.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool DungeonEvent::triggerEvent(Player &player)
{
    int roll = rand() % 100;

    if (roll < 20)
    {
        system("cls");
        cout << CYAN << "\n=== 랜덤 던전 이벤트 ===" << RESET << endl;

        int eventType = rand() % 2;

        if (eventType == 0)
        {
            cout << YELLOW << "앗! 구석에 숨겨진 낡은 보물상자를 발견했습니다!" << RESET << endl;
            int goldGain = rand() % 100 + 50 + (player.dungeonFloor * 5);
            player.gold += goldGain;
            cout << GREEN << "상자를 열어 " << goldGain << " 골드를 획득했습니다!" << RESET << endl;
        }
        else
        {
            cout << RED << "우드득... 함정을 밟았습니다! 천장에서 독화살이 날아옵니다!" << RESET << endl;
            int damage = 15 + (player.dungeonFloor * 2);
            player.takeDamage(damage);
        }

        cout << "\n엔터를 누르면 층을 돌파합니다...";
        cin.ignore();
        cin.get();
        return true;
    }

    return false;
}