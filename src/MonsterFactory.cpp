#include "../include/MonsterFactory.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Monster *MonsterFactory::spawnMonster(int floor, int playerLevel)
{
    string mName = "알 수 없는 몬스터";
    int mHp = 30 + (floor * 5);
    int mAtk = 5 + floor;

    ifstream file("monsters.csv");
    if (file.is_open())
    {
        string line;
        bool isFirstLine = true;

        while (getline(file, line))
        {
            if (isFirstLine)
            {
                isFirstLine = false;
                continue;
            }

            stringstream ss(line);
            string token;
            vector<string> data;

            while (getline(ss, token, ','))
            {
                data.push_back(token);
            }

            if (data.size() >= 4)
            {
                int targetFloor = stoi(data[0]);
                if (floor <= targetFloor)
                {
                    mName = data[1];
                    mHp = stoi(data[2]) + (floor * 3);
                    mAtk = stoi(data[3]) + (floor / 2);
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        if (floor >= 10)
        {
            mName = "오크 족장";
            mHp = 150;
            mAtk = 20;
        }
        else if (floor >= 5)
        {
            mName = "고블린 전사";
            mHp = 80;
            mAtk = 10;
        }
        else
        {
            mName = "야생의 슬라임";
            mHp = 30;
            mAtk = 5;
        }
    }

    return new Monster(mName, mHp, mAtk);
}