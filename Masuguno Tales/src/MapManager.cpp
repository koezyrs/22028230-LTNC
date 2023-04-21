#include "MapManager.h"

std::map<int, std::vector<std::vector<Tile>>> MapManager::mapBase;
std::map<int, std::shared_ptr<Map>> MapManager::mapDatabase;
void MapManager::LoadMap(int map_id)
{
    Game::currentMap = mapDatabase[map_id];
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

void MapManager::LoadMapDatabase()
{
    // Map Base
    mapBase[1] = setupMap("data files/maps/map01.msgn", 35, 30);
    mapBase[2] = setupMap("data files/maps/map02.msgn", 25, 20);
    mapBase[3] = setupMap("data files/maps/map03.msgn", 32, 18);

    // Map database
    mapDatabase[1] = std::make_shared<Map>(1, "Map01");
    mapDatabase[2] = std::make_shared<Map>(2, "Map02");
    mapDatabase[3] = std::make_shared<Map>(3, "Map02");

    // Load data
    LoadMap1();
    LoadMap2();
    LoadMap3();
}

void MapManager::LoadMap1()
{
    mapDatabase[1]->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[1]->AddNPC(15 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    mapDatabase[1]->AddNPC(7 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[1]->AddNPC(5 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    mapDatabase[1]->AddNPC(4 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[1]->AddNPC(13 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");

    mapDatabase[1]->AddEvent(14 * 32, 0, []{LoadMap(2); Game::gPlayer->setPosition(15*32,18*32);});
    mapDatabase[1]->AddEvent(15 * 32, 0, []{LoadMap(2); Game::gPlayer->setPosition(15*32,18*32);});
    mapDatabase[1]->AddEvent(16 * 32, 0, []{LoadMap(2); Game::gPlayer->setPosition(15*32,18*32);});
    mapDatabase[1]->AddEvent(17 * 32, 0, []{LoadMap(2); Game::gPlayer->setPosition(15*32,18*32);});
    mapDatabase[1]->AddEvent(18 * 32, 0, []{LoadMap(2); Game::gPlayer->setPosition(15*32,18*32);});
    mapDatabase[1]->AddEvent(19 * 32, 0, []{LoadMap(2); Game::gPlayer->setPosition(15*32,18*32);});

    mapDatabase[1]->AddEvent(0, 3*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 4*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 5*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 6*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 7*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 8*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 9*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 10*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 11*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 12*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 13*32, []{LoadMap(3);});
    mapDatabase[1]->AddEvent(0, 14*32, []{LoadMap(3);});


    mapDatabase[1]->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, 1, mapBase[1]);
    mapDatabase[1]->AddMonster(15 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[1]);
    mapDatabase[1]->AddMonster(8 * GAME_PIXELS, 9 * GAME_PIXELS, 1, mapBase[1]);
    mapDatabase[1]->AddMonster(7 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[1]);
}

void MapManager::LoadMap2()
{
    mapDatabase[2]->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[2]->AddNPC(15 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    mapDatabase[2]->AddNPC(7 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[2]->AddNPC(5 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    mapDatabase[2]->AddNPC(4 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[2]->AddNPC(13 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");

    mapDatabase[2]->AddEvent(13 * 32, 19*32, []{LoadMap(1);});
    mapDatabase[2]->AddEvent(14 * 32, 19*32, []{LoadMap(1);});
    mapDatabase[2]->AddEvent(15 * 32, 19*32, []{LoadMap(1);});
    mapDatabase[2]->AddEvent(16 * 32, 19*32, []{LoadMap(1);});

    mapDatabase[2]->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, 1, mapBase[2]);
    mapDatabase[2]->AddMonster(15 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[2]);
    mapDatabase[2]->AddMonster(8 * GAME_PIXELS, 9 * GAME_PIXELS, 1, mapBase[2]);
    mapDatabase[2]->AddMonster(7 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[2]);
}

void MapManager::LoadMap3()
{
    mapDatabase[3]->AddNPC(10 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[3]->AddNPC(15 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    mapDatabase[3]->AddNPC(7 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[3]->AddNPC(5 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");
    mapDatabase[3]->AddNPC(4 * GAME_PIXELS, 10 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[3]->AddNPC(13 * GAME_PIXELS, 20 * GAME_PIXELS, "Sprite-Guard2", "KienHDVN");

    mapDatabase[3]->AddEvent(11 * 32, 17*32, []{LoadMap(1);});
    mapDatabase[3]->AddEvent(12 * 32, 17*32, []{LoadMap(1);});
    mapDatabase[3]->AddEvent(13 * 32, 17*32, []{LoadMap(1);});
    mapDatabase[3]->AddEvent(14 * 32, 17*32, []{LoadMap(1);});

    mapDatabase[3]->AddMonster(10 * GAME_PIXELS, 10 * GAME_PIXELS, 1, mapBase[3]);
    mapDatabase[3]->AddMonster(15 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[3]);
    mapDatabase[3]->AddMonster(8 * GAME_PIXELS, 9 * GAME_PIXELS, 1, mapBase[3]);
    mapDatabase[3]->AddMonster(7 * GAME_PIXELS, 15 * GAME_PIXELS, 1, mapBase[3]);
}
