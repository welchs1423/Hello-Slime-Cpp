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
    cout << "=== 직업 선택 ===" << endl;
    cout << "1. 전사 (강한 체력과 물리 공격력)\n2. 마법사 (강력한 마법 공격력과 마나)\n3. 도적 (빠른 공격과 치명타)\n선택: ";
    cin >> jobClass;

    if (jobClass == 1)
        job = std::make_unique<Warrior>();
    else if (jobClass == 2)
        job = std::make_unique<Mage>();
    else if (jobClass == 3)
        job = std::make_unique<Rogue>();
    else
    {
        jobClass = 0;
        job = std::make_unique<Beginner>();
    }

    job->applyBonus(maxHp, hp, maxMp, mp, weaponDamage);
    hp = maxHp;
    mp = maxMp;
}

void Player::printStatus()
{
    string jName = "초보자";
    if (jobClass == 1)
        jName = "전사";
    else if (jobClass == 2)
        jName = "마법사";
    else if (jobClass == 3)
        jName = "도적";
    string pName = "없음";
    if (activePet == 1)
        pName = "전투 늑대";
    else if (activePet == 2)
        pName = "치유의 요정";

    cout << "\n[ " << name << " ] Lv." << level << " (" << jName << ")" << (rebirthCount > 0 ? " [환생 " + to_string(rebirthCount) + "회]" : "") << endl;
    cout << "동행 펫: " << pName << endl;
    cout << "체력: " << hp << "/" << maxHp << " | 마나: " << mp << "/" << maxMp << endl;
    cout << "공격력: " << str * 3 << " (+" << weaponDamage + (weaponLevel * 5) << ") | 방어력: " << vit * 2 << " (+" << armorDefense + (armorLevel * 3) << ")" << endl;
    cout << "경험치: " << exp << "/" << maxExp << " | 지갑: " << gold << "G | 예금: " << bankGold << "G" << endl;
}

void Player::openInventory()
{
    system("cls");
    cout << "=== 가방 ===" << endl;
    cout << "체력 포션: " << potions << "개 | 마나 포션: " << manaPotions << "개" << endl;
    cout << "\n[ 장비 및 아이템 ]" << endl;
    if (inventory.empty())
        cout << "가방이 비어있습니다." << endl;
    else
    {
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            cout << i + 1 << ". ";
            if (inventory[i].isEquipped)
                cout << "[E] ";
            cout << "[" << inventory[i].getTypeName() << "] " << inventory[i].name << " (효과: " << inventory[i].effectValue << ")" << endl;
        }
    }
    cout << "\n0. 닫기\n사용/장착할 아이템 번호: ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= inventory.size())
    {
        Item &item = inventory[choice - 1];
        if (item.type == 3)
        {
            if (potions > 0)
            {
                hp += item.effectValue;
                if (hp > maxHp)
                    hp = maxHp;
                potions--;
                inventory.erase(inventory.begin() + (choice - 1));
                cout << item.name << " 사용 완료!" << endl;
            }
        }
        else if (item.type == 4)
        {
            if (manaPotions > 0)
            {
                mp += item.effectValue;
                if (mp > maxMp)
                    mp = maxMp;
                manaPotions--;
                inventory.erase(inventory.begin() + (choice - 1));
                cout << item.name << " 사용 완료!" << endl;
            }
        }
        else if (item.type == 5)
        {
            cout << "만병통치약은 전투 중에만 사용할 수 있습니다." << endl;
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
                cout << item.name << " 장착 해제!" << endl;
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
                cout << item.name << " 장착 완료!" << endl;
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
    {
        cout << "남은 스탯 포인트가 없습니다." << endl;
        return;
    }
    while (statPoints > 0)
    {
        system("cls");
        cout << "=== 스탯 분배 (남은 포인트: " << statPoints << ") ===" << endl;
        cout << "1. 근력 (STR): " << str << "\n2. 지능 (INT): " << intel << "\n3. 체력 (VIT): " << vit << "\n0. 완료\n투자할 스탯 번호: ";
        int choice;
        cin >> choice;
        if (choice == 0)
            break;
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
}

void Player::resetStats()
{
    if (gold < 500)
    {
        cout << "골드가 부족합니다! (필요: 500G)" << endl;
        return;
    }
    int baseStr = 5 + (rebirthCount * 10);
    int baseInt = 5 + (rebirthCount * 10);
    int baseVit = 5 + (rebirthCount * 10);
    if (str == baseStr && intel == baseInt && vit == baseVit)
    {
        cout << "초기화할 스탯이 없습니다." << endl;
        return;
    }
    gold -= 500;
    maxMp -= ((intel - baseInt) * 5);
    if (mp > maxMp)
        mp = maxMp;
    maxHp -= ((vit - baseVit) * 10);
    if (hp > maxHp)
        hp = maxHp;
    statPoints += (str - baseStr) + (intel - baseInt) + (vit - baseVit);
    str = baseStr;
    intel = baseInt;
    vit = baseVit;
    cout << "500G를 지불하여 스탯을 초기화했습니다." << endl;
}

void Player::checkAchievements()
{
    if (!achMonsterHunter && totalKills >= 10)
    {
        achMonsterHunter = true;
        str += 5;
        cout << "\n[업적 달성] 몬스터 학살자! (영구 근력 +5)" << endl;
    }
    if (!achRichMan && (gold + bankGold) >= 3000)
    {
        achRichMan = true;
        vit += 5;
        maxHp += 50;
        hp += 50;
        cout << "\n[업적 달성] 벼락부자! (영구 체력 +5, 최대 체력 +50)" << endl;
    }
}

void Player::doRebirth()
{
    if (level < 50)
    {
        cout << RED << "환생은 50레벨 이상부터 가능합니다!" << RESET << endl;
        return;
    }
    rebirthCount++;
    level = 1;
    exp = 0;
    maxExp = 100;
    str = 5 + (rebirthCount * 10);
    intel = 5 + (rebirthCount * 10);
    vit = 5 + (rebirthCount * 10);
    maxHp = 100 + (rebirthCount * 50);
    hp = maxHp;
    maxMp = 50 + (rebirthCount * 20);
    mp = maxMp;
    statPoints = 0;
    dungeonFloor = 1;
    cout << MAGENTA << "\n!!! 환생의 불꽃이 타오릅니다 !!!\n기본 스탯이 폭발적으로 상승합니다!" << RESET << endl;
}

int Player::attack() { return str * 3 + weaponDamage + (weaponLevel * 5); }
int Player::magicAttack() { return intel * 4; }
void Player::takeDamage(int damage)
{
    int actualDamage = damage - (vit * 2 + armorDefense + (armorLevel * 3));
    if (actualDamage < 1)
        actualDamage = 1;
    hp -= actualDamage;
    cout << "플레이어가 " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << hp << ")" << endl;
}

void Player::heal() { hp = maxHp; }
void Player::restoreMp() { mp = maxMp; }
void Player::gainExp(int amount)
{
    if (level >= 50)
        return;
    exp += amount;
    cout << amount << " 경험치를 획득했습니다." << endl;
    while (exp >= maxExp && level < 50)
        levelUp();
    if (level >= 50)
    {
        exp = 0;
        cout << YELLOW << "만렙(Lv.50) 달성! 길드에서 환생할 수 있습니다." << RESET << endl;
    }
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
    cout << GREEN << "레벨 업! Lv." << level << " (스탯 포인트 +5)" << RESET << endl;
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
            outFile << safeName << " " << item.type << " " << item.effectValue << " " << item.price << " " << item.isEquipped << "\n";
        }
        outFile << "SKILL_SIZE " << skills.size() << "\n";
        for (const auto &skill : skills)
        {
            string safeName = skill.name;
            replace(safeName.begin(), safeName.end(), ' ', '_');
            outFile << safeName << " " << skill.mpCost << " " << skill.baseDamage << " " << skill.type << "\n";
        }
        outFile << "W_DUR " << weaponDurability << "\n";
        outFile << "A_DUR " << armorDurability << "\n";
        outFile << "INN_AFF " << innkeeperAffinity << "\n";
        outFile << "TOTAL_KILLS " << totalKills << "\n";
        outFile << "ACH_HUNTER " << achMonsterHunter << "\n";
        outFile << "ACH_RICH " << achRichMan << "\n";
        outFile << "REBIRTH_CNT " << rebirthCount << "\n";
        outFile << "PET " << activePet << "\n";
        int checksum = (level * 13) + (gold * 7) + maxHp + (rebirthCount * 3) + (bankGold * 2);
        outFile << "CHECKSUM " << checksum << "\n";
        outFile.close();
        cout << "게임이 성공적으로 저장되었습니다." << endl;
    }
}

void Player::load()
{
    ifstream inFile("savefile.txt");
    if (inFile.is_open())
    {
        string key;
        int value;
        int loadedChecksum = -1;
        inventory.clear();
        skills.clear();
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
                    inFile >> sName >> t >> v >> p >> e;
                    replace(sName.begin(), sName.end(), '_', ' ');
                    inventory.push_back(Item(sName, t, v, p, e));
                }
            }
            else if (key == "SKILL_SIZE")
            {
                for (int i = 0; i < value; i++)
                {
                    string sName;
                    int cost, dmg, t;
                    inFile >> sName >> cost >> dmg >> t;
                    replace(sName.begin(), sName.end(), '_', ' ');
                    skills.push_back(Skill(sName, cost, dmg, t));
                }
            }
            else if (key == "W_DUR")
                weaponDurability = value;
            else if (key == "A_DUR")
                armorDurability = value;
            else if (key == "INN_AFF")
                innkeeperAffinity = value;
            else if (key == "TOTAL_KILLS")
                totalKills = value;
            else if (key == "ACH_HUNTER")
                achMonsterHunter = value;
            else if (key == "ACH_RICH")
                achRichMan = value;
            else if (key == "REBIRTH_CNT")
                rebirthCount = value;
            else if (key == "PET")
                activePet = value;
            else if (key == "CHECKSUM")
                loadedChecksum = value;
        }
        inFile.close();
        int calculatedChecksum = (level * 13) + (gold * 7) + maxHp + (rebirthCount * 3) + (bankGold * 2);
        if (loadedChecksum != -1 && loadedChecksum != calculatedChecksum)
        {
            cout << RED << "경고: 세이브 파일 변조 감지! 소지 골드와 예금이 초기화됩니다." << RESET << endl;
            gold = 0;
            bankGold = 0;
        }
        if (jobClass == 1)
            job = std::make_unique<Warrior>();
        else if (jobClass == 2)
            job = std::make_unique<Mage>();
        else if (jobClass == 3)
            job = std::make_unique<Rogue>();
        else
            job = std::make_unique<Beginner>();
        cout << "게임을 성공적으로 불러왔습니다." << endl;
    }
}