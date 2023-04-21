#include "MapManager.h"

std::map<int, std::vector<std::vector<Tile>>> MapManager::mapBase;

void MapManager::LoadMap(int map_id)
{
    switch(map_id)
    {
    case 1:
        LoadMap1();
        break;
    case 2:
        LoadMap2();
        break;
    case 3:
        LoadMap3();
        break;
    }
}

void MapManager::LoadMapDatabase()
{
    mapBase[1] = setupMap("data files/maps/map01.msgn", 35, 30);
    mapBase[2] = setupMap("data files/maps/map02.msgn", 25, 20);
    mapBase[3] = setupMap("data files/maps/map03.msgn", 32, 18);
}

std::vector<std::vector<Tile>> MapManager::setupMap(const char* msgnFile, int sizeX, int sizeY)
{
    std::fstream fileContainCoordiate;
    char tile;

    std::vector<std::vector<Tile>> res;

    fileContainCoordiate.open(msgnFile);
    for(int y = 0; y < sizeY; y++)
    {
        std::vector<Tile> tmp;
        for(int x = 0 ; x < sizeX; x++)
        {
            fileContainCoordiate.get(tile);
            int id = atoi(&tile);
            if(id == 1)
            {
                Tile tmpTile = Tile(static_cast<float>(x), static_cast<float>(y), true);
                tmp.push_back(tmpTile);
            }else
            {
                Tile tmpTile = Tile(static_cast<float>(x), static_cast<float>(y), false);
                tmp.push_back(tmpTile);
            }
            fileContainCoordiate.ignore();
            //std::cout << id << " ";
        }
        //std::cout << std::endl;
        res.push_back(tmp);
    }
    fileContainCoordiate.close();
    return res;
}
void MapManager::LoadMap1()
{
    std::unique_ptr<Map> newMap = std::make_unique<Map>(1);
    Game::currentMap = std::move(newMap);
    Game::currentMap->LoadMap("Map01", mapBase[1]);
    Game::gPlayer->setPosition(16*32,32);

    Game::currentMap->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(15 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddNPC(7 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(5 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddNPC(4 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(13 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");

    Game::currentMap->AddEvent(14 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(15 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(16 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(17 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(18 * 32, 0, []{LoadMap2();});
    Game::currentMap->AddEvent(19 * 32, 0, []{LoadMap2();});

    Game::currentMap->AddEvent(0, 3*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 4*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 5*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 6*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 7*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 8*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 9*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 10*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 11*32, []{LoadMap3();});
    Game::currentMap->AddEvent(0, 12*32, []{LoadMap3();});

    Game::currentMap->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, 1, mapBase[1]);
    Game::currentMap->AddMonster(15 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[1]);
    Game::currentMap->AddMonster(8 * GAME_PIXELS, 9 * GAME_PIXELS, 1, mapBase[1]);
    Game::currentMap->AddMonster(7 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[1]);
}

void MapManager::LoadMap2()
{
    std::unique_ptr<Map> newMap = std::make_unique<Map>(2);
    Game::currentMap = std::move(newMap);
    Game::currentMap->LoadMap("Map02", mapBase[2]);
    Game::gPlayer->setPosition(14*32,18*32);

    Game::currentMap->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(15 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddNPC(7 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(5 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddNPC(4 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(13 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");

    Game::currentMap->AddEvent(13 * 32, 19*32, []{LoadMap1();});
    Game::currentMap->AddEvent(14 * 32, 19*32, []{LoadMap1();});
    Game::currentMap->AddEvent(15 * 32, 19*32, []{LoadMap1();});
    Game::currentMap->AddEvent(16 * 32, 19*32, []{LoadMap1();});

    Game::currentMap->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, 1, mapBase[2]);
    Game::currentMap->AddMonster(15 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[2]);
    Game::currentMap->AddMonster(8 * GAME_PIXELS, 9 * GAME_PIXELS, 1, mapBase[2]);
    Game::currentMap->AddMonster(7 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[2]);
}

void MapManager::LoadMap3()
{
    std::unique_ptr<Map> newMap = std::make_unique<Map>(3);
    Game::currentMap = std::move(newMap);
    Game::currentMap->LoadMap("Map03", mapBase[3]);
    Game::gPlayer->setPosition(15*32,16*32);

    Game::currentMap->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(15 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddNPC(7 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(5 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    Game::currentMap->AddNPC(4 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    Game::currentMap->AddNPC(13 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");

    Game::currentMap->AddEvent(11 * 32, 17*32, []{LoadMap1();});
    Game::currentMap->AddEvent(12 * 32, 17*32, []{LoadMap1();});
    Game::currentMap->AddEvent(13 * 32, 17*32, []{LoadMap1();});
    Game::currentMap->AddEvent(14 * 32, 17*32, []{LoadMap1();});

    Game::currentMap->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, 1, mapBase[3]);
    Game::currentMap->AddMonster(15 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[3]);
    Game::currentMap->AddMonster(8 * GAME_PIXELS, 9 * GAME_PIXELS, 1, mapBase[3]);
    Game::currentMap->AddMonster(7 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[3]);
}
