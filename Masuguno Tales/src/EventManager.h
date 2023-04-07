#pragma once
#ifndef EventManager_h
#define EventManager_h

#include <vector>

#include "Item.h"
#include "Equipment.h"
#include "Tile.h"

class Monster;

class EventManager
{
public:
    static void ChangeMap(int mapID);
    static bool AddEquipmentToInventory(Equipment* _equipment);
    static bool AddEquipmentToCharacterInformation(Equipment* _equipment);
    static bool AddItemToInventory(Item* _item);
    static Tile** getMapTiles();
    static int GetMapSizeX();
    static int GetMapSizeY();
    static void setNearestTarget();
    static void PerformSkill(Monster* monster, Vector2D currentplayerPos, std::string skillName);

};
#endif // EventManager_h
