#include "../include/EventManager.h"
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/GameActor.h"
#include "../include/Vector2D.h"

void EventManager::ChangeMap(int xpos, int ypos, float actorXPos, float actorYPos, const char* maptex, const char* mapfile, int sizeX, int sizeY)
{
    Game::currentMap->ClearMap();
    Game::currentMap->LoadMap(maptex, mapfile, sizeX, sizeY);
    Game::gPlayer->getTransformComponent()->position = Vector2D{actorXPos,actorYPos};
}
