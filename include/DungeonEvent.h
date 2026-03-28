#ifndef DUNGEONEVENT_H
#define DUNGEONEVENT_H

#include "Player.h"

class DungeonEvent
{
public:
    // 이벤트가 발생하면 true를 반환하여 해당 층의 전투를 스킵함
    static bool triggerEvent(Player &player);
};

#endif