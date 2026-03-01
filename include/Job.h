#ifndef JOB_H
#define JOB_H

#include <string>

class Job {
public:
    virtual ~Job() {}
    virtual std::string getName() = 0;
    
    virtual void applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) {}
    
    virtual int attack(int level, int weaponDamage, int weaponLevel, int str) = 0;
    virtual int magicAttack(int level, int weaponDamage, int intel) = 0;
};

class Beginner : public Job {
public:
    std::string getName() override;
    int attack(int level, int weaponDamage, int weaponLevel, int str) override;
    int magicAttack(int level, int weaponDamage, int intel) override;
};

class Warrior : public Job {
public:
    std::string getName() override;
    void applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) override;
    int attack(int level, int weaponDamage, int weaponLevel, int str) override;
    int magicAttack(int level, int weaponDamage, int intel) override;
};

class Mage : public Job {
public:
    std::string getName() override;
    void applyBonus(int& maxHp, int& hp, int& maxMp, int& mp, int& weaponDmg) override;
    int attack(int level, int weaponDamage, int weaponLevel, int str) override;
    int magicAttack(int level, int weaponDamage, int intel) override;
};

class Rogue : public Job {
public:
    std::string getName() override;
    int attack(int level, int weaponDamage, int weaponLevel, int str) override;
    int magicAttack(int level, int weaponDamage, int intel) override;
};

#endif