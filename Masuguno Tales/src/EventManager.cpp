#include "EventManager.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

#include "Game.h"
#include "Map.h"
#include "MapManager.h"
#include "Vector2D.h"

#include "Actor.h"
#include "HUD.h"
#include "Inventory.h"
#include "CharacterInformation.h"


#include "Database/SkillDB.h"
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

void EventManager::SetSystemMessage(std::string _message, Uint64 timeout)
{
    Game::gHUD->setSystemMessage(_message, timeout);
}
