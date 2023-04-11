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
    static void SetSystemMessage(std::string _message, Uint64 timeout);

};
#endif // EventManager_h
