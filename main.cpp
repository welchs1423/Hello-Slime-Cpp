#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameManager.h" // ✨ 게임 매니저 불러오기

using namespace std;

int main() {
    system("chcp 65001");
    srand(time(0)); 

    GameManager game; // 게임 엔진 시동
    game.run();       // 게임 실행!
    
    return 0;
}