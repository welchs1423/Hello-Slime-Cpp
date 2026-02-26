#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int level;
    int exp;
    int maxHp;
    int hp;
    int potions;
    int gold;   // Added Gold
    int weaponDamage;   // Added Weapon Damage
    int dungeonFloor;   // Added Dungeon Floor

    Player(); 
    int attack(); 
    void takeDamage(int damage); 
    void heal(); 
    void gainExp(int amount); 
    void printStatus(); 

    // File I/O for Save & Load
    void save();
    bool load();
};

#endif