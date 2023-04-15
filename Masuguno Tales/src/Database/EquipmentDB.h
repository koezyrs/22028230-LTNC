#pragma once
#ifndef EquipmentDB_h
#define EquipmentDB_h

#include <map>
#include <string>
#include "../Settings.h"

struct EquipmentType
{
    int equipment_id;
    std::string spriteName;
    EQUIPMENT_TAG equipmentTag;
    std::string equipmentName;
    int Strength;
    int Dexterity;
    int Intelligence;
    int Vitality;
    int Agility;
    EquipmentType() {}
    EquipmentType(int _equipment_id, std::string _spriteName, EQUIPMENT_TAG _equipmentTag, std::string _equipmentName,
                     int _strength, int _dexterity, int _intelligence, int _vitality, int _agility)
                : equipment_id(_equipment_id), spriteName(_spriteName), equipmentTag(_equipmentTag),
                equipmentName(_equipmentName), Strength(_strength), Dexterity(_dexterity), Intelligence(_intelligence),
                Vitality(_vitality), Agility(_agility) {}

};

class EquipmentDB
{
public:
    static void LoadEquipmentDatabase();
    static std::map<int, EquipmentType> equipmentDatabase;
};

#endif // EquipmentDB_h
