#include "../include/Player.h"
#include "../include/Job.h"
#include "../include/Colors.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Player::Player() {
    name = "Hero";
    level = 1;
    maxHp = 100; hp = 100;
    maxMp = 50;  mp = 50;
    weaponDamage = 5;
    armorDefense = 0;
    exp = 0; maxExp = 100;
    gold = 100;
    potions = 3; manaPotions = 1;
    dungeonFloor = 1;
    weaponLevel = 0;
    armorLevel = 0;
    jobClass = 0;
    job = nullptr;

    inventory.push_back(Item("초보자의 빵", 3, 20, 10));

    updateJobLogic(); // 직업 객체 초기화
    registerStats();  // 저장 레지스트리 등록
}

Player::~Player() {
    if (job) delete job; // 메모리 누수 방지
}

// ✨ 자동 저장/불러오기 레지스트리
void Player::registerStats() {
    stats["level"] = &level;
    stats["maxHp"] = &maxHp;
    stats["hp"] = &hp;
    stats["maxMp"] = &maxMp;
    stats["mp"] = &mp;
    stats["weaponDamage"] = &weaponDamage;
    stats["armorDefense"] = &armorDefense;
    stats["exp"] = &exp;
    stats["maxExp"] = &maxExp;
    stats["gold"] = &gold;
    stats["potions"] = &potions;
    stats["manaPotions"] = &manaPotions;
    stats["dungeonFloor"] = &dungeonFloor;
    stats["weaponLevel"] = &weaponLevel;
    stats["armorLevel"] = &armorLevel;
    stats["jobClass"] = &jobClass;
}

// ✨ 직업 객체 교체
void Player::updateJobLogic() {
    if (job) delete job;
    if (jobClass == 1) job = new Warrior();
    else if (jobClass == 2) job = new Mage();
    else if (jobClass == 3) job = new Rogue();
    else job = new Beginner();
}

// ✨ 게임 시작 시 직업 선택
void Player::chooseClass() {
    system("cls");
    cout << CYAN << "\n=== ✨ 직업을 선택하세요 ✨ ===" << RESET << endl;
    cout << "1. 🗡️ 전사 (보너스: 최대 체력 +50, 공격력 +5)\n";
    cout << "2. 🧙 마법사 (보너스: 최대 마나 +50, 강력한 마법 데미지)\n";
    cout << "3. 🗡️ 도적 (보너스: 크리티컬 확률 40%)\n";
    cout << "선택: ";
    cin >> jobClass;

    updateJobLogic();
    job->applyBonus(maxHp, hp, maxMp, mp, weaponDamage);

    cout << YELLOW << "\n당신은 이제 위대한 [" << job->getName() << "] 입니다!" << RESET << endl;
    cout << "엔터를 누르면 모험을 시작합니다...";
    cin.ignore();
    cin.get();
}

// ✨ 상태창 출력
void Player::printStatus() {
    cout << "\n[" << CYAN << "Lv." << level << " " << job->getName() << RESET << "] "
         << "HP: " << GREEN << hp << "/" << maxHp << RESET << " | "
         << "MP: " << CYAN << mp << "/" << maxMp << RESET << " | "
         << "EXP: " << YELLOW << exp << "/" << maxExp << RESET << endl;
    cout << "ATK: " << weaponDamage << " (+" << weaponLevel * 5 << ") | "
         << "DEF: " << armorDefense << " (+" << armorLevel * 3 << ") | "
         << "Gold: " << YELLOW << gold << "G" << RESET << endl;
}

// ✨ 공격 (Job에게 위임)
int Player::attack() {
    return job->attack(level, weaponDamage, weaponLevel);
}

// ✨ 마법 공격 (Job에게 위임)
int Player::magicAttack() {
    if (mp >= 20) {
        mp -= 20;
        return job->magicAttack(level, weaponDamage);
    } else {
        cout << RED << "❌ 마나가 부족합니다!" << RESET << endl;
        return -1;
    }
}

// ✨ 피격 (방어구 강화 수치 반영)
void Player::takeDamage(int damage) {
    int bonusDefense = armorLevel * 3; 
    int actualDamage = damage - armorDefense - bonusDefense;
    if(actualDamage < 0) actualDamage = 0; 

    hp -= actualDamage;
    cout << RED << "적의 공격! " << actualDamage << "의 데미지를 입었습니다. (방어력으로 " << armorDefense + bonusDefense << " 감소)" << RESET << endl;
}

void Player::heal() {
    if (potions > 0) {
        potions--;
        hp += 50;
        if (hp > maxHp) hp = maxHp;
        cout << GREEN << "포션을 사용했습니다! (+50 HP) 남은 포션: " << potions << RESET << endl;
    } else cout << RED << "포션이 부족합니다!" << RESET << endl;
}

void Player::restoreMp() {
    if (manaPotions > 0) {
        manaPotions--;
        mp += 50;
        if (mp > maxMp) mp = maxMp;
        cout << CYAN << "마나 포션을 사용했습니다! (+50 MP) 남은 마나 포션: " << manaPotions << RESET << endl;
    } else cout << RED << "마나 포션이 부족합니다!" << RESET << endl;
}

void Player::gainExp(int amount) {
    exp += amount;
    cout << YELLOW << amount << "의 경험치를 획득했습니다!" << RESET << endl;
    if (exp >= maxExp) levelUp();
}

void Player::levelUp() {
    level++;
    exp -= maxExp;
    maxExp += 50;
    maxHp += 20; hp = maxHp;
    maxMp += 10; mp = maxMp;
    weaponDamage += 2;
    cout << GREEN << "🎉 레벨 업! Lv." << level << "이 되었습니다!" << RESET << endl;
}

void Player::save() {
    ofstream outFile("savefile.txt");
    if (outFile.is_open()) {
        for (auto const& [key, val] : stats) {
            outFile << key << " " << *val << "\n";
        }
        outFile.close();
        cout << GREEN << "💾 게임이 성공적으로 저장되었습니다." << RESET << endl;
    } else cout << RED << "❌ 저장 파일을 열 수 없습니다!" << RESET << endl;
}

void Player::load() {
    ifstream inFile("savefile.txt");
    if (inFile.is_open()) {
        string key;
        int value;
        while (inFile >> key >> value) {
            if (stats.find(key) != stats.end()) *stats[key] = value;
        }
        inFile.close();
        updateJobLogic(); // ✨ 불러온 jobClass 숫자에 맞춰 직업 세팅!
        cout << GREEN << "📂 게임을 성공적으로 불러왔습니다." << RESET << endl;
    } else cout << RED << "❌ 저장 파일이 없습니다. 새로운 게임을 시작합니다." << RESET << endl;
}

void Player::openInventory() {
    system("cls");
    cout << CYAN << "\n=== 가방 (인벤토리) ===" << RESET << endl;

    if (inventory.empty()){
        cout << "가방이 텅 비어있습니다." << endl;
    } else {
        cout << "총 " << inventory.size() << "개의 아이템이 있습니다.\n" << endl;
        for (size_t i = 0; i < inventory.size(); i++){
            cout << i + 1 << ". [" << inventory[i].getTypeName() << "] "
                 << YELLOW << inventory[i].name << RESET
                 << " (효과 수치: " << inventory[i].effectValue << ")" << endl;
        }
    }
    cout << "\n엔터를 누르면 닫습니다...";
    cin.ignore();
    cin.get();
}