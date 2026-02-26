#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int level;
    int exp;
    int maxHp;
    int maxMp;  // Added Max Mp
    int mp;     // Added Current Mp
    int hp;
    int potions;
    int gold;   // Added Gold
    int weaponDamage;   // Added Weapon Damage
    int armorDefense;   // Added Armor Defense
    int dungeonFloor;   // Added Dungeon Floor

    Player(); 
    int attack(); 
    int magicAttack();  // Added Magic Attack Skill
    void takeDamage(int damage); 
    void heal(); 
    void gainExp(int amount); 
    void printStatus(); 

    // File I/O for Save & Load
    void save();
    bool load();
};

#endif