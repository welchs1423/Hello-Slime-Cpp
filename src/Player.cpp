#include "../include/Player.h"
#include "../include/Job.h"
#include "../include/Colors.h"
#include "../include/InputHelpers.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static bool copyFileBytes(const string &src, const string &dst)
{
    ifstream in(src, ios::binary);
    if (!in.is_open())
        return false;
    ofstream out(dst, ios::binary | ios::trunc);
    if (!out.is_open())
        return false;
    vector<char> buf(4096);
    while (in)
    {
        in.read(buf.data(), static_cast<streamsize>(buf.size()));
        streamsize got = in.gcount();
        if (got > 0)
            out.write(buf.data(), got);
    }
    return true;
}

static bool tryLoadFromPath(Player &player, const string &path, bool isBackup)
{
    ifstream inFile(path);
    if (!inFile.is_open())
        return false;

    string key;
    int value;
    int loadedChecksum = -1;

    player.inventory.clear();
    player.skills.clear();

    while (inFile >> key >> value)
    {
        if (player.stats.find(key) != player.stats.end())
        {
            *player.stats[key] = value;
        }
        else if (key == "INVENTORY_SIZE")
        {
            int size = value;
            for (int i = 0; i < size; i++)
            {
                string safeName;
                int t, v, p;
                bool e;
                inFile >> safeName >> t >> v >> p >> e;
                replace(safeName.begin(), safeName.end(), '_', ' ');
                player.inventory.push_back(Item(safeName, t, v, p, e));
            }
        }
        else if (key == "SKILL_SIZE")
        {
            int size = value;
            for (int i = 0; i < size; i++)
            {
                string safeName;
                int cost, dmg, t;
                inFile >> safeName >> cost >> dmg >> t;
                replace(safeName.begin(), safeName.end(), '_', ' ');
                player.skills.push_back(Skill(safeName, cost, dmg, t));
            }
        }
        else if (key == "TOTAL_KILLS")
            player.totalKills = value;
        else if (key == "ACH_HUNTER")
            player.achMonsterHunter = value;
        else if (key == "ACH_RICH")
            player.achRichMan = value;
        else if (key == "CHECKSUM")
            loadedChecksum = value;
        else if (key == "W_DUR")
            player.weaponDurability = value;
        else if (key == "A_DUR")
            player.armorDurability = value;
    }
    inFile.close();

    int calculatedChecksum = (player.level * 13) + (player.gold * 7) + player.maxHp;
    if (loadedChecksum != -1 && loadedChecksum != calculatedChecksum)
    {
        if (!isBackup)
            return false;

        cout << "경고: 백업 세이브 파일도 무결성 검증에 실패했습니다. 골드가 0으로 초기화됩니다." << endl;
        player.gold = 0;
    }

    if (player.jobClass == 1)
        player.job = std::make_unique<Warrior>();
    else if (player.jobClass == 2)
        player.job = std::make_unique<Mage>();
    else if (player.jobClass == 3)
        player.job = std::make_unique<Rogue>();
    else
        player.job = std::make_unique<Beginner>();

    return true;
}

static string formatPlayTime(int totalSec)
{
    if (totalSec < 0)
        totalSec = 0;
    int h = totalSec / 3600;
    int m = (totalSec % 3600) / 60;
    int s = totalSec % 60;
    string out;
    if (h > 0)
        out += to_string(h) + "시간 ";
    if (h > 0 || m > 0)
        out += to_string(m) + "분 ";
    out += to_string(s) + "초";
    return out;
}

Player::Player()
{
    name = "Hero";
    level = 1;
    maxHp = 100;
    hp = 100;
    maxMp = 50;
    mp = 50;
    weaponDamage = 5;
    armorDefense = 0;
    exp = 0;
    maxExp = 100;
    gold = 100;
    potions = 3;
    manaPotions = 1;
    dungeonFloor = 1;
    weaponLevel = 0;
    armorLevel = 0;
    jobClass = 0;
    job = nullptr;
    activeQuestId = 0;
    questProgress = 0;
    weaponDurability = 50;
    armorDurability = 50;
    str = 5;
    intel = 5;
    vit = 5;
    statPoints = 0;

    totalKills = 0;
    achMonsterHunter = false;
    achRichMan = false;
    totalPlaySeconds = 0;
    autoPotionEnabled = 0;
    autoPotionThreshold = 30;
    autoManaPotionEnabled = 0;
    autoManaPotionThreshold = 30;

    inventory.push_back(Item("초보자의 빵", 3, 20, 10));

    updateJobLogic();
    registerStats();
}

Player::~Player()
{
}

void Player::registerStats()
{
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
    stats["activeQuestId"] = &activeQuestId;
    stats["questProgress"] = &questProgress;
    stats["str"] = &str;
    stats["intel"] = &intel;
    stats["vit"] = &vit;
    stats["statPoints"] = &statPoints;
    stats["playSeconds"] = &totalPlaySeconds;
    stats["autoPotionEnabled"] = &autoPotionEnabled;
    stats["autoPotionThreshold"] = &autoPotionThreshold;
    stats["autoManaPotionEnabled"] = &autoManaPotionEnabled;
    stats["autoManaPotionThreshold"] = &autoManaPotionThreshold;
}

// 직업 세팅 및 기본 스킬 지급
void Player::updateJobLogic()
{
    skills.clear();

    if (jobClass == 1)
    {
        job = std::make_unique<Warrior>();
        skills.push_back(Skill("파워 스트라이크", 10, 20, 1));
    }
    else if (jobClass == 2)
    {
        job = std::make_unique<Mage>();
        skills.push_back(Skill("파이어볼", 15, 25, 2));
    }
    else if (jobClass == 3)
    {
        job = std::make_unique<Rogue>();
        skills.push_back(Skill("독 찌르기", 10, 15, 1));
    }
    else
    {
        job = std::make_unique<Beginner>();
        skills.push_back(Skill("달팽이 세마리", 5, 10, 1));
    }
}

void Player::chooseClass()
{
    system("cls");
    cout << CYAN << "\n=== ✨ 직업을 선택하세요 ✨ ===" << RESET << endl;
    cout << "1. 🗡️ 전사 (보너스: 최대 체력 +50, 공격력 +5)\n";
    cout << "2. 🧙 마법사 (보너스: 최대 마나 +50, 강력한 마법 데미지)\n";
    cout << "3. 🗡️ 도적 (보너스: 크리티컬 확률 40%)\n";
    cout << "선택: ";
    jobClass = readIntInRange(1, 3);

    updateJobLogic();
    job->applyBonus(maxHp, hp, maxMp, mp, weaponDamage);

    cout << YELLOW << "\n당신은 이제 위대한 [" << job->getName() << "] 입니다!" << RESET << endl;
    cout << "엔터를 누르면 모험을 시작합니다...";
    cin.ignore();
    cin.get();
}

void Player::printStatus()
{
    cout << "\n[" << CYAN << "Lv." << level << " " << job->getName() << RESET << "] "
         << "HP: " << GREEN << hp << "/" << maxHp << RESET << " | "
         << "MP: " << CYAN << mp << "/" << maxMp << RESET << " | "
         << "EXP: " << YELLOW << exp << "/" << maxExp << RESET << endl;
    cout << "던전 최고 도달 층: " << CYAN << dungeonFloor << "층" << RESET << " | "
         << "누적 플레이: " << formatPlayTime(totalPlaySeconds) << endl;
    cout << "자동 체력 포션: " << (autoPotionEnabled ? GREEN : RED)
         << (autoPotionEnabled ? "ON" : "OFF") << RESET
         << " (HP " << autoPotionThreshold << "% 이하)" << " | "
         << "자동 마나 포션: " << (autoManaPotionEnabled ? GREEN : RED)
         << (autoManaPotionEnabled ? "ON" : "OFF") << RESET
         << " (MP " << autoManaPotionThreshold << "% 이하)" << endl;
    cout << "ATK: " << weaponDamage << " (+" << weaponLevel * 5 << ") | "
         << "DEF: " << armorDefense << " (+" << armorLevel * 3 << ") | "
         << "Gold: " << YELLOW << gold << "G" << RESET << endl;

    if (activeQuestId > 0)
    {
        cout << YELLOW << "[📜 퀘스트 진행 중] 임무 번호: " << activeQuestId
             << " | 진척도: " << questProgress << RESET << endl;
    }

    cout << "[스탯] STR: " << str << " | INT: " << intel << " | VIT: " << vit
         << " | " << YELLOW << "남은 포인트: " << statPoints << RESET << endl;
}

int Player::attack() { return job->attack(level, weaponDamage, weaponLevel, str); }

int Player::magicAttack()
{
    if (mp >= 20)
    {
        mp -= 20;
        return job->magicAttack(level, weaponDamage, intel);
    }
    else
    {
        cout << RED << "❌ 마나가 부족합니다!" << RESET << endl;
        return -1;
    }
}

void Player::takeDamage(int damage)
{
    int bonusDefense = armorLevel * 3;
    int actualDamage = damage - armorDefense - bonusDefense;
    if (actualDamage < 0)
        actualDamage = 0;
    hp -= actualDamage;
    cout << RED << "적의 공격! " << actualDamage << "의 데미지를 입었습니다. (방어력으로 " << armorDefense + bonusDefense << " 감소)" << RESET << endl;
}

void Player::heal()
{
    if (potions > 0)
    {
        potions--;
        hp += 50;
        if (hp > maxHp)
            hp = maxHp;
        cout << GREEN << "포션을 사용했습니다! (+50 HP) 남은 포션: " << potions << RESET << endl;
    }
    else
        cout << RED << "포션이 부족합니다!" << RESET << endl;
}

bool Player::tryAutoHeal()
{
    if (!autoPotionEnabled || potions <= 0 || maxHp <= 0)
        return false;

    int hpPercent = (hp * 100) / maxHp;
    if (hpPercent <= autoPotionThreshold)
    {
        cout << YELLOW << "[자동 포션] 체력이 위험 구간(" << hpPercent
             << "%)에 진입해 포션을 자동 사용합니다." << RESET << endl;
        heal();
        return true;
    }
    return false;
}

void Player::restoreMp()
{
    if (manaPotions > 0)
    {
        manaPotions--;
        mp += 50;
        if (mp > maxMp)
            mp = maxMp;
        cout << CYAN << "마나 포션을 사용했습니다! (+50 MP) 남은 마나 포션: " << manaPotions << RESET << endl;
    }
    else
        cout << RED << "마나 포션이 부족합니다!" << RESET << endl;
}

bool Player::tryAutoRestoreMp()
{
    if (!autoManaPotionEnabled || manaPotions <= 0 || maxMp <= 0)
        return false;

    int mpPercent = (mp * 100) / maxMp;
    if (mpPercent <= autoManaPotionThreshold)
    {
        cout << YELLOW << "[자동 마나 포션] 마나가 부족 구간(" << mpPercent
             << "%)에 진입해 마나 포션을 자동 사용합니다." << RESET << endl;
        restoreMp();
        return true;
    }
    return false;
}

void Player::openCombatSettings()
{
    while (true)
    {
        system("cls");
        cout << CYAN << "\n=== 전투 보조 설정 ===" << RESET << endl;
        cout << "1. 자동 체력 포션 ON/OFF (현재: "
             << (autoPotionEnabled ? "ON" : "OFF") << ")\n";
        cout << "2. 자동 체력 포션 발동 기준 (현재: HP "
             << autoPotionThreshold << "% 이하)\n";
        cout << "3. 자동 마나 포션 ON/OFF (현재: "
             << (autoManaPotionEnabled ? "ON" : "OFF") << ")\n";
        cout << "4. 자동 마나 포션 발동 기준 (현재: MP "
             << autoManaPotionThreshold << "% 이하)\n";
        cout << "0. 설정 종료\n선택: ";

        int choice = readIntInRange(0, 4);
        if (choice == 0)
            return;

        if (choice == 1)
        {
            autoPotionEnabled = autoPotionEnabled ? 0 : 1;
            cout << YELLOW << "자동 체력 포션이 "
                 << (autoPotionEnabled ? "활성화" : "비활성화")
                 << "되었습니다." << RESET << endl;
        }
        else if (choice == 2)
        {
            cout << "체력 포션 발동 기준을 선택하세요. (20~70%)\n";
            cout << "1. 20%  2. 30%  3. 40%  4. 50%  5. 60%  6. 70%\n선택: ";
            int thresholdChoice = readIntInRange(1, 6);
            autoPotionThreshold = thresholdChoice * 10 + 10;
            cout << GREEN << "자동 체력 포션 발동 기준이 HP "
                 << autoPotionThreshold << "% 이하로 변경되었습니다."
                 << RESET << endl;
        }
        else if (choice == 3)
        {
            autoManaPotionEnabled = autoManaPotionEnabled ? 0 : 1;
            cout << YELLOW << "자동 마나 포션이 "
                 << (autoManaPotionEnabled ? "활성화" : "비활성화")
                 << "되었습니다." << RESET << endl;
        }
        else
        {
            cout << "마나 포션 발동 기준을 선택하세요. (20~70%)\n";
            cout << "1. 20%  2. 30%  3. 40%  4. 50%  5. 60%  6. 70%\n선택: ";
            int thresholdChoice = readIntInRange(1, 6);
            autoManaPotionThreshold = thresholdChoice * 10 + 10;
            cout << GREEN << "자동 마나 포션 발동 기준이 MP "
                 << autoManaPotionThreshold << "% 이하로 변경되었습니다."
                 << RESET << endl;
        }

        cout << "\n엔터를 누르면 계속합니다...";
        cin.ignore();
        cin.get();
    }
}

void Player::gainExp(int amount)
{
    if (level >= 50)
    {
        cout << "이미 최대 레벨에 도달하여 더 이상 경험치를 얻을 수 없습니다." << endl;
        return;
    }

    exp += amount;
    cout << amount << " 경험치를 획득했습니다. (" << exp << "/" << maxExp << ")" << endl;

    while (exp >= maxExp && level < 50)
    {
        levelUp();
    }

    if (level >= 50)
    {
        exp = 0;
        cout << "만렙(Lv.50)을 달성했습니다. 축하합니다." << endl;
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
    cout << "레벨 업! Lv." << level << "이 되었습니다. (스탯 포인트 +5)" << endl;
}

void Player::openInventory()
{
    bool inInventory = true;

    while (inInventory)
    {
        system("cls");
        cout << CYAN << "\n=== 🎒 가방 (인벤토리) ===" << RESET << endl;

        if (inventory.empty())
        {
            cout << "가방이 텅 비어있습니다." << endl;
            cout << "\n엔터를 누르면 닫습니다...";
            cin.ignore();
            cin.get();
            return;
        }

        cout << "총 " << inventory.size() << "개의 아이템이 있습니다.\n"
             << endl;
        for (size_t i = 0; i < inventory.size(); i++)
        {
            cout << i + 1 << ". ";
            // ✨ 장착 중인 아이템이면 앞에 [E] 마크를 붙여줍니다!
            if (inventory[i].isEquipped)
            {
                cout << GREEN << "[E] " << RESET;
            }
            cout << "[" << inventory[i].getTypeName() << "] "
                 << YELLOW << inventory[i].name << RESET
                 << " (효과: " << inventory[i].effectValue << ")" << endl;
        }

        cout << "\n0. 가방 닫기\n사용/장착할 아이템 번호를 입력하세요: ";
        int choice;
        cin >> choice;

        if (choice == 0)
        {
            inInventory = false;
        }
        else if (choice > 0 && choice <= inventory.size())
        {
            int index = choice - 1;

            Item &selectedItem = inventory[index];

            // 1. 무기 장착 (가방에서 삭제 안 됨)
            if (selectedItem.type == 1)
            {
                // 기존 장착 무기 해제
                for (auto &item : inventory)
                {
                    if (item.type == 1)
                        item.isEquipped = false;
                }

                selectedItem.isEquipped = true; // 새 무기 장착
                weaponDamage = selectedItem.effectValue;
                cout << GREEN << "\n"
                     << selectedItem.name << "을(를) 장착했습니다! (기본 공격력 " << weaponDamage << ")" << RESET << endl;
            }
            // 2. 방어구 장착 (가방에서 삭제 안 됨)
            else if (selectedItem.type == 2)
            {
                // 기존 장착 방어구 해제
                for (auto &item : inventory)
                {
                    if (item.type == 2)
                        item.isEquipped = false;
                }

                selectedItem.isEquipped = true; // 새 방어구 장착
                armorDefense = selectedItem.effectValue;
                cout << GREEN << "\n"
                     << selectedItem.name << "을(를) 장착했습니다! (기본 방어력 " << armorDefense << ")" << RESET << endl;
            }
            // 3. 소모품 (사용한 뒤 가방에서 삭제됨)
            else if (selectedItem.type == 3)
            {
                hp += selectedItem.effectValue;
                if (hp > maxHp)
                    hp = maxHp;
                if (potions > 0)
                    potions--;
                cout << GREEN << "\n"
                     << selectedItem.name << "을(를) 사용해 체력을 " << selectedItem.effectValue << " 회복했습니다!" << RESET << endl;
                inventory.erase(inventory.begin() + index); // ✨ 소모품만 삭제
            }
            else if (selectedItem.type == 4)
            {
                mp += selectedItem.effectValue;
                if (mp > maxMp)
                    mp = maxMp;
                if (manaPotions > 0)
                    manaPotions--;
                cout << CYAN << "\n"
                     << selectedItem.name << "을(를) 사용해 마나를 " << selectedItem.effectValue << " 회복했습니다!" << RESET << endl;
                inventory.erase(inventory.begin() + index); // ✨ 소모품만 삭제
            }
            else
            {
                cout << RED << "\n"
                     << selectedItem.name << "은(는) 당장 쓸 수 없습니다. 길가에 버렸습니다." << RESET << endl;
                inventory.erase(inventory.begin() + index); // ✨ 잡템 버리기
            }

            cout << "엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
        else
        {
            cout << RED << "잘못된 번호입니다." << RESET << endl;
            cout << "엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}

void Player::save()
{
    // 저장 전 기존 세이브를 백업해 둔다.
    copyFileBytes("savefile.txt", "savefile.bak");

    ofstream outFile("savefile.txt");
    if (outFile.is_open())
    {
        for (auto const &[key, val] : stats)
        {
            outFile << key << " " << *val << "\n";
        }

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

        outFile << "TOTAL_KILLS " << totalKills << "\n";
        outFile << "ACH_HUNTER " << achMonsterHunter << "\n";
        outFile << "ACH_RICH " << achRichMan << "\n";

        int checksum = (level * 13) + (gold * 7) + maxHp;
        outFile << "W_DUR " << weaponDurability << "\n";
        outFile << "A_DUR " << armorDurability << "\n";
        outFile << "CHECKSUM " << checksum << "\n";

        outFile.close();
        cout << "게임이 성공적으로 저장되었습니다." << endl;
    }
    else
        cout << "저장 파일을 열 수 없습니다!" << endl;
}

void Player::load()
{
    if (tryLoadFromPath(*this, "savefile.txt", false))
    {
        cout << "게임을 성공적으로 불러왔습니다." << endl;
        return;
    }

    cout << "경고: 세이브 파일이 손상되었거나 변조되었습니다. 백업 세이브로 복구를 시도합니다..." << endl;
    if (tryLoadFromPath(*this, "savefile.bak", true))
    {
        cout << "백업 세이브로 복구에 성공했습니다. 진행 상황을 저장해 정상화합니다..." << endl;
        save();
        return;
    }

    cout << "저장 파일이 없습니다. 새로운 게임을 시작합니다." << endl;
}
void Player::allocateStats()
{
    while (statPoints > 0)
    {
        system("cls");
        cout << CYAN << "\n=== 스탯 분배 ===" << RESET << endl;
        cout << "잔여 스탯 포인트: " << YELLOW << statPoints << RESET << "\n"
             << endl;
        cout << "1. 근력(STR) 올리기 (현재 " << str << ") - 물리 공격력 증가" << endl;
        cout << "2. 지능(INT) 올리기 (현재 " << intel << ") - 마법 공격력 및 최대 마나 증가" << endl;
        cout << "3. 체력(VIT) 올리기 (현재 " << vit << ") - 최대 체력 증가" << endl;
        cout << "0. 분배 종료\n 선택: ";

        int choice;
        cin >> choice;

        if (choice == 0)
            break;
        else if (choice == 1)
        {
            str++;
            statPoints--;
            cout << GREEN << "근력이 1 올랐습니다!" << RESET << endl;
        }
        else if (choice == 2)
        {
            intel++;
            statPoints--;
            maxMp += 5;
            mp += 5;
            cout << CYAN << "지능이 1 올랐습니다! (최대 마나 +5)" << RESET << endl;
        }
        else if (choice == 3)
        {
            vit++;
            statPoints--;
            maxHp += 10;
            hp += 10;
            cout << GREEN << "체력이 1 올랐습니다! (최대 체력 +10)" << RESET << endl;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }
    }

    if (statPoints <= 0)
    {
        cout << "\n모든 스탯 포인트를 소모했습니다.\n엔터를 누르면 돌아갑니다...";
        cin.ignore();
        cin.get();
    }
}

void Player::resetStats()
{
    cout << "\n=== 스탯 초기화 ===" << endl;
    if (gold < 500)
    {
        cout << "골드가 부족합니다! (필요: 500G)" << endl;
        return;
    }
    if (str == 5 && intel == 5 && vit == 5)
    {
        cout << "초기화할 스탯이 없습니다." << endl;
        return;
    }

    gold -= 500;

    int investedStr = str - 5;
    int investedIntel = intel - 5;
    int investedVit = vit - 5;

    maxMp -= (investedIntel * 5);
    if (mp > maxMp)
        mp = maxMp;

    maxHp -= (investedVit * 10);
    if (hp > maxHp)
        hp = maxHp;

    str = 5;
    intel = 5;
    vit = 5;

    int refundedPoints = investedStr + investedIntel + investedVit;
    statPoints += refundedPoints;

    cout << "500G를 지불하여 스탯을 초기화했습니다." << endl;
    cout << "반환된 스탯 포인트: " << refundedPoints << endl;
}

void Player::checkAchievements()
{
    if (!achMonsterHunter && totalKills >= 10)
    {
        achMonsterHunter = true;
        cout << "\n========================================" << endl;
        cout << " [업적 달성] 몬스터 학살자 (10마리 처치)" << endl;
        cout << " 보상: 영구 근력(STR) +5 증가!" << endl;
        cout << "========================================" << endl;
        str += 5;
    }

    if (!achRichMan && gold >= 3000)
    {
        achRichMan = true;
        cout << "\n========================================" << endl;
        cout << " [업적 달성] 벼락부자 (3000 골드 보유)" << endl;
        cout << " 보상: 영구 체력(VIT) +5 증가!" << endl;
        cout << "========================================" << endl;
        vit += 5;
        maxHp += 50;
        hp += 50;
    }
}