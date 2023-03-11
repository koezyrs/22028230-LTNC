#include <iostream>
#include "EventManager.h"
#include "Game.h"
#include "Map.h"
#include "MapManager.h"
#include "Actor.h"
#include "Vector2D.h"

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
