#pragma once
#ifndef EventManager_h
#define EventManager_h

#include "Equipment.h"

class EventManager
{
public:
    static void ChangeMap(int mapID);
    static bool AddEquipmentToInventory(Equipment* _equipment);
    static bool AddEquipmentToCharacterInformation(Equipment* _equipment);
};
#endif // EventManager_h
