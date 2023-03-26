#include "EventManager.h"

#include <iostream>
#include "Game.h"
#include "Map.h"
#include "MapManager.h"
#include "Vector2D.h"

#include "Actor.h"
#include "Inventory.h"
#include "CharacterInformation.h"

void EventManager::ChangeMap(int mapID)
{
    switch(mapID){
    case 1:
        MapManager::LoadMap1();
        break;
    case 2:
        MapManager::LoadMap2();
        break;
    }
}

bool EventManager::AddEquipmentToInventory(Equipment* _equipment)
{
    return Game::gInventory->AddEquipment(_equipment);
}

bool EventManager::AddEquipmentToCharacterInformation(Equipment* _equipment)
{
    return Game::gCharacterInformation->AddEquipment(_equipment);
}

bool EventManager::AddItemToInventory(Item* _item)
{
    return Game::gInventory->AddItem(_item);
}

Tile** EventManager::getMapTiles()
{
    return Game::currentMap->tiles;
}
