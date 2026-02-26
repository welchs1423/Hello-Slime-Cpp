# Hello Slime CPP
My first toy project to understand the procedural and object-oriented flow of C++ in a VSC environment.

## Changelog

### [2026-02-27]
- **Armor Enhancement System**: Implemented armor upgrading (+3 DEF per level) and added it to the automated save registry to balance the endgame combat loop.
- **Implemented Gacha System**: Added 'Mystery Box' to the shop with randomized rewards (Gold jackpot, potions, free weapon upgrades, or failure) to act as a gold sink and add RNG fun.
- **Implemented Polymorphic Abilities**: Overrode `attack()` method for `Orc` and `Slime` to introduce unique monster skills (Heavy Smash, Acid Spit) without modifying combat logic.
- **Architectural Refactoring**: Implemented `MonsterFactory` to decouple monster spawning from `Battle` logic.
- **New Content**: Added `Orc` monster with higher stats for advanced dungeon floors.
- **Directory Clean-up**: Finalized `/src` and `/include` separation for better scalability.
- **Expanded Bestiary**: Added 'Orc' monster using the inheritance system.
- **Dynamic Encounter Logic**: Updated dungeon spawning to introduce tougher enemies at higher floors.
- **Corrected Project Structure**: Moved `main.cpp` and configuration files from a literal `/Root` folder to the actual project root directory.
- **Finalized Build Pipeline**: Confirmed the standardized g++ command with include and src pathing.
- Implemented Weapon Enhancement system (+1, +2...) with dynamic damage scaling.
- Automated Save/Load system using Metadata Registry (Member Pointer Map).
- Added Mana Potion item to Shop and Battle system to allow MP restoration.
- Performed deep OOP refactoring: Abstracted `Shop` and `Battle` into dedicated classes to fully decouple logic from `GameManager`.
- Refactored core loop into `GameManager` class for improved modularity and cleaner `main.cpp`.
- Added Armor Defense system and expanded Shop with Leather/Iron Armors.
- Pivoted back to Console UI; Added MP (Mana Points) and Magic Skill system.
- Added Player HP display during combat for better visibility.
- Applied ANSI Escape Codes to colorize UI elements (HP, Gold, Damage) for better UX.
- Added UI polish (Console Screen Clear) and expanded Shop items (Steel Sword).
- Added Dungeon Floor progression and King Slime Boss battles.
- Added Town phase, Gold drop system, and Item Shop (Weapons/Potions).
- Localized all code comments and console outputs to English.
- Implemented Game Save/Load feature using `fstream`.
- Refactored `Slime` class and finalized OOP modularization.
- Separated header (`.h`) and source (`.cpp`) files for `Player` class.

### [2026-02-26]
- Added infinite dungeon loop and EXP-based level-up system.

### [2026-02-25]
- Added Critical Hit system (20% chance).
- Added Healing Potion system (Max HP cap & usage limits).
- Set up `.gitignore` and optimized project folder.
- Fixed terminal encoding issues (applied `chcp 65001`).
- Implemented basic turn-based battle loop with wild slimes.