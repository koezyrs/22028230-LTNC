#include "Game.h"
#include "Actor.h"
#include "Map.h"
#include "MapManager.h"
#include "Event.h"
#include "Event/EventType.h"
#include "Settings.h"
void MapManager::LoadMap1()
{
    Game::currentMap->ClearMap();
    Game::currentMap->LoadMap("data files/maps/map01.png", "data files/maps/map01.msgn", 35, 30);
    Game::currentMap->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "data files/graphics/characters/158.png", "The Guard");
    Game::currentMap->AddNPC(20 * GAME_PIXELS, 20 * GAME_PIXELS, "data files/graphics/characters/159.png", "KienHDVN");
    Game::currentMap->AddEvent(new ChangeMapEvent(14 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(15 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(16 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(17 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(18 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(19 * GAME_PIXELS, 0,2));
    Game::currentMap->AddMonster(5 * GAME_PIXELS, 5 * GAME_PIXELS, "data files/graphics/cow.png", "Cow Special", 1);
    Game::gPlayer->getTransformComponent()->position = Vector2D{14 * GAME_PIXELS, 1* GAME_PIXELS};
}

void MapManager::LoadMap2()
{
    Game::currentMap->ClearMap();
    Game::currentMap->LoadMap("data files/maps/map02.png", "data files/maps/map02.msgn", 25, 20);
    Game::currentMap->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, "data files/graphics/cow.png", "Cow Special", 1);
    Game::currentMap->AddEvent(new ChangeMapEvent(13 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::currentMap->AddEvent(new ChangeMapEvent(14 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::currentMap->AddEvent(new ChangeMapEvent(15 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::currentMap->AddEvent(new ChangeMapEvent(16 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::gPlayer->getTransformComponent()->position = Vector2D{14 * GAME_PIXELS, 18 * GAME_PIXELS};
}
