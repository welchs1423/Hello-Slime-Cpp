#ifndef JOB_H
#define JOB_H

#include <string>

class Job {
public:
    virtual ~Job() {}
    virtual std::string getName() = 0;
    
    // 직업 선택 시 부여되는 보너스 스탯
    virtual void applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) {}
    
    // 직업별 고유 공격 및 마법 로직
    virtual int attack(int level, int weaponDamage, int weaponLevel) = 0;
    virtual int magicAttack(int level, int weaponDamage) = 0;
};

// --- 각각의 직업들 (상속) ---
class Beginner : public Job {
public:
    std::string getName() override;
    int attack(int level, int weaponDamage, int weaponLevel) override;
    int magicAttack(int level, int weaponDamage) override;
};

class Warrior : public Job {
public:
    std::string getName() override;
    void applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) override;
    int attack(int level, int weaponDamage, int weaponLevel) override;
    int magicAttack(int level, int weaponDamage) override;
};

class Mage : public Job {
public:
    std::string getName() override;
    void applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) override;
    int attack(int level, int weaponDamage, int weaponLevel) override;
    int magicAttack(int level, int weaponDamage) override;
};

class Rogue : public Job {
public:
    std::string getName() override;
    int attack(int level, int weaponDamage, int weaponLevel) override;
    int magicAttack(int level, int weaponDamage) override;
};

#endif