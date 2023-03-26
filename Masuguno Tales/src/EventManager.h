#pragma once
#ifndef EventManager_h
#define EventManager_h

#include "Item.h"
#include "Equipment.h"
#include "Tile.h"

class EventManager
{
public:
    static void ChangeMap(int mapID);
    static bool AddEquipmentToInventory(Equipment* _equipment);
    static bool AddEquipmentToCharacterInformation(Equipment* _equipment);
    static bool AddItemToInventory(Item* _item);
    static Tile** getMapTiles();
};
#endif // EventManager_h
