#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
class GameManager {
private:
    Player player;  // 매니저가 플레이어 정보를 관리함
    bool isPlaying;

    void clearScreen();
    void enterDungeon();    // 던전 로직
    void visitShop();       // 상점 로직

public:
    GameManager();
    void run(); // 메인 게임 루프 실행
};

#endif