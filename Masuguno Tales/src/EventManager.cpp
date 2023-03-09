#include <iostream>
#include "../include/EventManager.h"
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/MapManager.h"
#include "../include/Actor.h"
#include "../include/Vector2D.h"

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
