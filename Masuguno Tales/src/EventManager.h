#pragma once
#ifndef EventManager_h
#define EventManager_h

#include "Equipment.h"
#include "Item.h"

class EventManager
{
public:
    static void ChangeMap(int mapID);
    static bool AddEquipmentToInventory(Equipment* _equipment);
    static bool AddEquipmentToCharacterInformation(Equipment* _equipment);
    static bool AddItemToInventory(Item* _item);
};
#endif // EventManager_h
