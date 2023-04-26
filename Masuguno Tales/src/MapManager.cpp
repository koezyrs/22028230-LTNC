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
        }
        fileContainCoordiate.ignore();
        res.push_back(tmp);
    }
    fileContainCoordiate.close();
    return res;
}

void MapManager::LoadMapDatabase()
{
    // Map Base
    mapBase[1] = setupMap("data files/maps/map01.msgn", 50, 30);
    mapBase[2] = setupMap("data files/maps/map02.msgn", 33, 21);
    mapBase[3] = setupMap("data files/maps/map03.msgn", 61, 32);
    mapBase[4] = setupMap("data files/maps/map04.msgn", 60, 33);

    // Map database
    mapDatabase[1] = std::make_shared<Map>(1, "Map01", "Map01_Overlay");
    mapDatabase[2] = std::make_shared<Map>(2, "Map02", "Map02_Overlay");
    mapDatabase[3] = std::make_shared<Map>(3, "Map03", "Map03_Overlay");
    mapDatabase[4] = std::make_shared<Map>(4, "Map04", "Map04_Overlay");

    // Load data
    LoadMap1();
    LoadMap2();
    LoadMap3();
    LoadMap4();
}

void MapManager::LoadMap1()
{
    mapDatabase[1]->AddNPC(8 * GAME_PIXELS, 4 * GAME_PIXELS, "Sprite-Guard1", "The Guard");
    mapDatabase[1]->AddEvent(10 * 32, 14 * 32, []
                                {
                                    LoadMap(2);
                                    Game::gPlayer->setPosition(16 * 32, 19 * 32);
                                });
    mapDatabase[1]->AddEvent(-1 * 32, 23 * 32, []
                                {
                                    LoadMap(3);
                                    Game::gPlayer->setPosition(60 * 32, 17 * 32);
                                });
    mapDatabase[1]->AddEvent(-1 * 32, 24 * 32, []
                                {
                                    LoadMap(3);
                                    Game::gPlayer->setPosition(60 * 32, 18 * 32);
                                });
    mapDatabase[1]->AddEvent(35 * 32, 30 * 32, []
                                {
                                    LoadMap(4);
                                    Game::gPlayer->setPosition(27 * 32, 0 * 32);
                                });

}

void MapManager::LoadMap2()
{
    mapDatabase[2]->AddEvent(16 * 32, 20 * 32, []
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(10 * 32, 16 * 32);
                                });
}

void MapManager::LoadMap3()
{
    mapDatabase[3]->AddEvent(61 * 32, 17 * 32, []
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(0 * 32, 23 * 32);
                                });
    mapDatabase[3]->AddEvent(61 * 32, 18 * 32, []
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(0 * 32, 24 * 32);
                                });
}

void MapManager::LoadMap4()
{
    mapDatabase[4]->AddEvent(27 * 32, -1 * 32, []
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(35 * 32, 29 * 32);
                                });
}
