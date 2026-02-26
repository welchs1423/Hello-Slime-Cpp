# Hello Slime CPP
My first toy project to understand the procedural and object-oriented flow of C++ in a VSC environment.

## Changelog

### [2026-02-27]
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