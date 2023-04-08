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

int EventManager::GetMapSizeX()
{
    return Game::currentMap->getSizeX();
}

int EventManager::GetMapSizeY()
{
    return Game::currentMap->getSizeY();
}

void EventManager::setNearestTarget()
{
    int distanceToNearestTarget = 320; // Scan radious
    Vector2D playerPos = Game::gPlayer->getTransformComponent()->position;
    for(auto& monster : Game::currentMap->monsters)
    {
        Vector2D monsterPos = monster->getTransformComponent()->position;
        int distance = playerPos.DistanceTo(monsterPos);
        if(distance < distanceToNearestTarget)
        {
            distanceToNearestTarget = distance;
            Monster* oldTarget = Game::gPlayer->getKeyboardController()->getTarget();
            if(oldTarget != nullptr) oldTarget->unTargeted();
            Game::gPlayer->getKeyboardController()->setTarget(monster);
            monster->setTargeted();
        }
    }
    if(distanceToNearestTarget == 320)
    {
        Monster* oldTarget = Game::gPlayer->getKeyboardController()->getTarget();
        if(oldTarget != nullptr) oldTarget->unTargeted();
        Game::gPlayer->getKeyboardController()->setTarget(nullptr);
    }
}

bool EventManager::PerformSkill(Monster* monster, Vector2D currentplayerPos, std::string skillName)
{
    if(monster == nullptr) return false;
    SkillType sk = SkillDB::skillDatabase[skillName];
    if(sk.skillName.empty())
    {
        std::cerr << "No skill as " << skillName << "! Please check Skill Database";
        return false;
    }else
    {
        // Attack Monster
        Vector2D monsterPos = monster->getTransformComponent()->position;
        float distance = sqrt((monsterPos.x - currentplayerPos.x)*(monsterPos.x - currentplayerPos.x) + (monsterPos.y - currentplayerPos.y)*(monsterPos.y - currentplayerPos.y));

        float skillRange = sk.skillRange;
        if( (distance <= GAME_PIXELS + skillRange) && (monster->isTargeted()) )
        {
            float offsetX = 32;
            float offsetY = 32;
            monster->setTrigger();
            Game::currentMap->AddProjectile(monsterPos.x - offsetX, monsterPos.y - offsetY, sk.skillFrames, sk.skillSprite, sk.damage);
        }else return false;
    }
    return true;
}

void EventManager::SetSystemMessage(std::string _message, Uint64 timeout)
{
    Game::gHUD->setSystemMessage(_message, timeout);
}
