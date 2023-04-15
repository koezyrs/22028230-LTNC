#include "MapManager.h"

void MapManager::LoadMap1()
{
    Game::currentMap->ClearMap();
    Game::currentMap->LoadMap("Map01", "data files/maps/map01.msgn", 35, 30);
    Game::gPlayer->setPosition(16*32,32);

    Game::currentMap->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(20 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddEvent(14 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(15 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(16 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(17 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(18 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(19 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddMonster(5 * GAME_PIXELS, 5 * GAME_PIXELS, 1);
    Game::currentMap->AddMonster(5 * GAME_PIXELS, 10 * GAME_PIXELS, 1);
    Game::currentMap->AddMonster(5 * GAME_PIXELS, 15 * GAME_PIXELS, 1);
    Game::currentMap->AddMonster(5 * GAME_PIXELS, 20 * GAME_PIXELS, 1);
    Game::currentMap->AddMonster(10 * GAME_PIXELS, 5 * GAME_PIXELS, 1);
}

void MapManager::LoadMap2()
{
    Game::currentMap->ClearMap();
    Game::currentMap->LoadMap("Map02", "data files/maps/map02.msgn", 25, 20);
    Game::gPlayer->setPosition(14*32,18*32);
    Game::currentMap->AddEvent(13 * 32, 19*32, []{LoadMap1();});
    Game::currentMap->AddEvent(14 * 32, 19*32, []{LoadMap1();});
    Game::currentMap->AddEvent(15 * 32, 19*32, []{LoadMap1();});
    Game::currentMap->AddEvent(16 * 32, 19*32, []{LoadMap1();});
}
