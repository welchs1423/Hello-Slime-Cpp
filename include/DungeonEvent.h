#ifndef DUNGEONEVENT_H
#define DUNGEONEVENT_H

#include "Player.h"

class DungeonEvent {
public:
    // 플레이어의 상태를 변경할 수 있도록 참조(&)로 받는다.
    static bool triggerEvent(Player& player);
};

#endif