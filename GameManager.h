#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Shop.h"   // ✨ 상점 설계도 포함
#include "Battle.h" // ✨ 전투 설계도 포함

class GameManager {
private:
    Player player; 
    Shop shop;     // ✨ 상점 객체 생성
    Battle battle; // ✨ 전투 객체 생성
    bool isPlaying;

public:
    GameManager();
    void run(); 
};

#endif