#include "../include/Player.h"
#include "../include/Job.h"
#include "../include/Colors.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Player::Player()
{
    name = "모험가";
    level = 1;
    maxHp = 100;
    hp = 100;
    maxMp = 50;
    mp = 50;
    weaponDamage = 0;
    armorDefense = 0;
    exp = 0;
    maxExp = 100;
    gold = 500;
    potions = 3;
    manaPotions = 1;
    dungeonFloor = 1;
    weaponLevel = 0;
    armorLevel = 0;
    str = 5;
    intel = 5;
    vit = 5;
    statPoints = 0;
    weaponDurability = 50;
    armorDurability = 50;
    totalKills = 0;
    achMonsterHunter = false;
    achRichMan = false;
    innkeeperAffinity = 0;
    rebirthCount = 0;
    activePet = 0;
    bankGold = 0;
    jobClass = 0;
    activeQuestId = 0;
    questProgress = 0;
    registerStats();
    job = std::make_unique<Beginner>();
}

Player::~Player() {}

void Player::registerStats()
{
    stats["LEVEL"] = &level;
    stats["MAX_HP"] = &maxHp;
    stats["HP"] = &hp;
    stats["MAX_MP"] = &maxMp;
    stats["MP"] = &mp;
    stats["WEAPON_DMG"] = &weaponDamage;
    stats["ARMOR_DEF"] = &armorDefense;
    stats["EXP"] = &exp;
    stats["MAX_EXP"] = &maxExp;
    stats["GOLD"] = &gold;
    stats["POTIONS"] = &potions;
    stats["MANA_POTIONS"] = &manaPotions;
    stats["DUNGEON_FLOOR"] = &dungeonFloor;
    stats["WEAPON_LEVEL"] = &weaponLevel;
    stats["ARMOR_LEVEL"] = &armorLevel;
    stats["STR"] = &str;
    stats["INT"] = &intel;
    stats["VIT"] = &vit;
    stats["STAT_POINTS"] = &statPoints;
    stats["JOB_CLASS"] = &jobClass;
    stats["ACTIVE_QUEST"] = &activeQuestId;
    stats["QUEST_PROG"] = &questProgress;
    stats["BANK_GOLD"] = &bankGold;
}

void Player::chooseClass()
{
    system("cls");
    cout << "=== 직업 선택 ===\n1. 전사\n2. 마법사\n3. 도적\n선택: ";
    cin >> jobClass;
    if (jobClass == 1)
        job = std::make_unique<Warrior>();
    else if (jobClass == 2)
        job = std::make_unique<Mage>();
    else if (jobClass == 3)
        job = std::make_unique<Rogue>();
    else
        job = std::make_unique<Beginner>();
    job->applyBonus(maxHp, hp, maxMp, mp, weaponDamage);
    hp = maxHp;
    mp = maxMp;
}

void Player::printStatus()
{
    string jName = (jobClass == 1) ? "전사" : (jobClass == 2) ? "마법사"
                                          : (jobClass == 3)   ? "도적"
                                                              : "초보자";
    cout << "\n[ " << name << " ] Lv." << level << " (" << jName << ")" << (rebirthCount > 0 ? " [환생 " + to_string(rebirthCount) + "회]" : "") << endl;
    cout << "체력: " << hp << "/" << maxHp << " | 마나: " << mp << "/" << maxMp << endl;
    cout << "공격력: " << attack() << " | 지갑: " << gold << "G | 예금: " << bankGold << "G" << endl;
}

void Player::openInventory()
{
    system("cls");
    cout << "=== 가방 ===\n\n[ 장비 및 아이템 ]" << endl;
    if (inventory.empty())
        cout << "가방이 비어있습니다." << endl;
    else
    {
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            cout << i + 1 << ". ";
            if (inventory[i].isEquipped)
                cout << "[E] ";
            cout << "[" << inventory[i].getTypeName() << "] " << inventory[i].name;
            if (inventory[i].socketGem == 1)
                cout << RED << " (루비 장착됨)" << RESET;
            else if (inventory[i].socketGem == 2)
                cout << CYAN << " (사파이어 장착됨)" << RESET;
            cout << " (효과: " << inventory[i].effectValue << ")" << endl;
        }
    }
    cout << "\n0. 닫기\n선택: ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= inventory.size())
    {
        Item &item = inventory[choice - 1];
        if (item.type == 3 || item.type == 4)
        {
            hp += (item.type == 3) ? item.effectValue : 0;
            mp += (item.type == 4) ? item.effectValue : 0;
            if (hp > maxHp)
                hp = maxHp;
            if (mp > maxMp)
                mp = maxMp;
            inventory.erase(inventory.begin() + (choice - 1));
            cout << item.name << " 사용 완료!" << endl;
        }
        else if (item.type == 6)
        { // 보석 장착 로직
            cout << "보석을 장착할 무기를 선택하세요 (장착 중인 무기 권장): " << endl;
            for (size_t i = 0; i < inventory.size(); ++i)
            {
                if (inventory[i].type == 1)
                    cout << i + 1 << ". " << inventory[i].name << endl;
            }
            int target;
            cin >> target;
            if (target > 0 && target <= inventory.size() && inventory[target - 1].type == 1)
            {
                inventory[target - 1].socketGem = (item.name.find("루비") != string::npos) ? 1 : 2;
                cout << GREEN << inventory[target - 1].name << "에 보석을 성공적으로 박았습니다!" << RESET << endl;
                inventory.erase(inventory.begin() + (choice - 1));
            }
        }
        else if (item.type == 1 || item.type == 2)
        {
            if (item.isEquipped)
            {
                item.isEquipped = false;
                if (item.type == 1)
                    weaponDamage = 0;
                else
                    armorDefense = 0;
            }
            else
            {
                for (auto &invItem : inventory)
                {
                    if (invItem.type == item.type)
                        invItem.isEquipped = false;
                }
                item.isEquipped = true;
                if (item.type == 1)
                    weaponDamage = item.effectValue;
                else
                    armorDefense = item.effectValue;
            }
        }
        cout << "엔터를 누르면 계속합니다...";
        cin.ignore();
        cin.get();
    }
}

void Player::allocateStats()
{
    if (statPoints <= 0)
        return;
    cout << "1. STR  2. INT  3. VIT  0. 취소\n선택: ";
    int choice;
    cin >> choice;
    if (choice == 1)
        str++;
    else if (choice == 2)
    {
        intel++;
        maxMp += 5;
    }
    else if (choice == 3)
    {
        vit++;
        maxHp += 10;
        hp += 10;
    }
    statPoints--;
}

void Player::resetStats()
{
    if (gold < 500)
        return;
    gold -= 500;
    int base = 5 + (rebirthCount * 10);
    statPoints += (str - base) + (intel - base) + (vit - base);
    str = base;
    intel = base;
    vit = base;
}

void Player::checkAchievements()
{
    if (!achMonsterHunter && totalKills >= 10)
    {
        achMonsterHunter = true;
        str += 5;
    }
    if (!achRichMan && (gold + bankGold) >= 3000)
    {
        achRichMan = true;
        vit += 5;
    }
}

void Player::doRebirth()
{
    if (level < 50)
        return;
    rebirthCount++;
    level = 1;
    exp = 0;
    maxExp = 100;
    str = intel = vit = 5 + (rebirthCount * 10);
    maxHp = 100 + (rebirthCount * 50);
    hp = maxHp;
    maxMp = 50 + (rebirthCount * 20);
    mp = maxMp;
    dungeonFloor = 1;
}

int Player::attack()
{
    int base = str * 3 + weaponDamage + (weaponLevel * 5);
    // 보석 보너스: 루비(1) 면 공격력 20 추가
    for (auto &item : inventory)
    {
        if (item.isEquipped && item.type == 1 && item.socketGem == 1)
            base += 20;
    }
    return base;
}

int Player::magicAttack() { return intel * 4; }
void Player::takeDamage(int damage)
{
    int actual = damage - (vit * 2 + armorDefense + (armorLevel * 3));
    if (actual < 1)
        actual = 1;
    hp -= actual;
}

void Player::heal() { hp = maxHp; }
void Player::restoreMp() { mp = maxMp; }
void Player::gainExp(int amount)
{
    if (level >= 50)
        return;
    exp += amount;
    while (exp >= maxExp && level < 50)
        levelUp();
}
void Player::levelUp()
{
    level++;
    exp -= maxExp;
    maxExp += 50;
    maxHp += 10;
    hp = maxHp;
    maxMp += 5;
    mp = maxMp;
    statPoints += 5;
}

void Player::save()
{
    ofstream outFile("savefile.txt");
    if (outFile.is_open())
    {
        for (auto const &[key, val] : stats)
            outFile << key << " " << *val << "\n";
        outFile << "INVENTORY_SIZE " << inventory.size() << "\n";
        for (const auto &item : inventory)
        {
            string safeName = item.name;
            replace(safeName.begin(), safeName.end(), ' ', '_');
            outFile << safeName << " " << item.type << " " << item.effectValue << " " << item.price << " " << item.isEquipped << " " << item.socketGem << "\n";
        }
        outFile << "W_DUR " << weaponDurability << "\n";
        outFile << "A_DUR " << armorDurability << "\n";
        outFile << "REBIRTH_CNT " << rebirthCount << "\n";
        outFile << "BANK_GOLD " << bankGold << "\n";
        outFile.close();
    }
}

void Player::load()
{
    ifstream inFile("savefile.txt");
    if (inFile.is_open())
    {
        string key;
        int value;
        inventory.clear();
        while (inFile >> key >> value)
        {
            if (stats.find(key) != stats.end())
                *stats[key] = value;
            else if (key == "INVENTORY_SIZE")
            {
                for (int i = 0; i < value; i++)
                {
                    string sName;
                    int t, v, p;
                    bool e;
                    int g;
                    inFile >> sName >> t >> v >> p >> e >> g;
                    replace(sName.begin(), sName.end(), '_', ' ');
                    Item temp(sName, t, v, p, e);
                    temp.socketGem = g;
                    inventory.push_back(temp);
                }
            }
            else if (key == "BANK_GOLD")
                bankGold = value;
            else if (key == "REBIRTH_CNT")
                rebirthCount = value;
        }
        inFile.close();
    }
}