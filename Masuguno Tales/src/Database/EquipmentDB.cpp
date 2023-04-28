#include "EquipmentDB.h"

std::map<int, EquipmentType> EquipmentDB::equipmentDatabase;

void EquipmentDB::LoadEquipmentDatabase()
{
    equipmentDatabase[1] = EquipmentType(
        1,                      // id
        "Equip-AssasinDagger",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Assassin Dagger",      // Equipment Name
        "Assasin Dagger from the acient assassin! This is a powerful dagger! \nStrength: 5\nDexterity: 0\nIntelligence: 5\nVitality: 5\nAgility: 15",
        5,                      // Strength
        0,                      // Dex
        5,                      // Int
        5,                      // Vit
        15,                      // Agi
        30,                      // Buy Price
        5                        // Sell Price
    );
}
