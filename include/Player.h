#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

class Job; // 전방 선언 (전략 패턴을 위해 필요)

class Player {
public:
    // --- 플레이어 기본 스탯 ---
    std::string name;
    int level;
    int maxHp;
    int hp;
    int maxMp;
    int mp;
    int weaponDamage;
    int armorDefense;
    int exp;
    int maxExp; // 추가됨
    int gold;
    int potions;
    int manaPotions;
    int dungeonFloor;
    int weaponLevel;
    int armorLevel; // 추가됨
    
    // --- 직업 관련 변수 ---
    int jobClass;   // 추가됨
    Job* job;       // 추가됨

    // --- 저장 시스템용 맵 ---
    std::map<std::string, int*> stats;

    // --- 생성자 및 소멸자 ---
    Player();
    ~Player(); // 메모리 관리를 위해 추가됨

    // --- 핵심 시스템 함수 ---
    void registerStats();
    void updateJobLogic(); // 추가됨
    void chooseClass();    // 추가됨
    
    // --- 행동 함수 ---
    void printStatus();
    int attack();
    int magicAttack();
    void takeDamage(int damage);
    void heal();
    void restoreMp();
    void gainExp(int amount);
    void levelUp();        // 추가됨

    // --- 세이브/로드 (void로 통일) ---
    void save();
    void load();
};

#endif