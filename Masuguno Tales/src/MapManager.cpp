#include "../include/Game.h"
#include "../include/Actor.h"
#include "../include/Map.h"
#include "../include/MapManager.h"
#include "../include/Event.h"
#include "../include/Event/EventType.h"
#include "../include/Config.h"
void MapManager::LoadMap1()
{
    Game::currentMap->ClearMap();
    Game::currentMap->Refresh();
    Game::currentMap->LoadMap("assets/map01.png", "assets/map01.msgn", 35, 30);
    Game::currentMap->AddMonster(300, 300, "assets/cow.png");
    Game::currentMap->AddMonster(500, 300, "assets/cow.png");
    Game::currentMap->AddMonster(300, 500, "assets/cow.png");
    Game::currentMap->AddMonster(350, 600, "assets/cow.png");
    Game::currentMap->AddMonster(390, 700, "assets/cow.png");
    Game::currentMap->AddEvent(new ChangeMapEvent(14 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(15 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(16 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(17 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(18 * GAME_PIXELS, 0,2));
    Game::currentMap->AddEvent(new ChangeMapEvent(19 * GAME_PIXELS, 0,2));
    Game::gPlayer->getTransformComponent()->position = Vector2D{14 * GAME_PIXELS, 1* GAME_PIXELS};
}

void MapManager::LoadMap2()
{
    Game::currentMap->ClearMap();
    Game::currentMap->Refresh();
    Game::currentMap->LoadMap("assets/map02.png", "assets/map02.msgn", 25, 20);
    Game::currentMap->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, "assets/cow.png");
    Game::currentMap->AddEvent(new ChangeMapEvent(13 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::currentMap->AddEvent(new ChangeMapEvent(14 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::currentMap->AddEvent(new ChangeMapEvent(15 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::currentMap->AddEvent(new ChangeMapEvent(16 * GAME_PIXELS, 19 * GAME_PIXELS,1));
    Game::gPlayer->getTransformComponent()->position = Vector2D{14 * GAME_PIXELS, 18 * GAME_PIXELS};
}
