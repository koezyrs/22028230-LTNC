#include "MapManager.h"

std::map<int, std::vector<std::vector<Tile>>> MapManager::mapBase;
std::map<int, std::shared_ptr<Map>> MapManager::mapDatabase;
void MapManager::LoadMap(int map_id)
{
    Game::gPlayer->getKeyboardController()->unsetTarget();
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
    mapBase[5] = setupMap("data files/maps/map05.msgn", 32, 19);

    // Map database
    mapDatabase[1] = std::make_shared<Map>(1, "Map01", "Map01_Overlay");
    mapDatabase[2] = std::make_shared<Map>(2, "Map02", "Map02_Overlay");
    mapDatabase[3] = std::make_shared<Map>(3, "Map03", "Map03_Overlay");
    mapDatabase[4] = std::make_shared<Map>(4, "Map04", "Map04_Overlay");
    mapDatabase[5] = std::make_shared<Map>(5, "Map05", "");

    // Load data
    LoadMap1();
    LoadMap2();
    LoadMap3();
    LoadMap4();
    LoadMap5();
}

void MapManager::LoadMap1()
{
    mapDatabase[1]->AddNPC(8 * 32, 4 * 32, "Sprite-Leiea", "Leiea Lv. 6");
    mapDatabase[1]->AddEvent(10 * 32, 14 * 32, "",[]
                                {
                                    LoadMap(2);
                                    Game::gPlayer->setPosition(16 * 32, 19 * 32);
                                });
    mapDatabase[1]->AddEvent(-1 * 32, 23 * 32, "",[]
                                {
                                    LoadMap(3);
                                    Game::gPlayer->setPosition(59 * 32, 17 * 32);
                                });
    mapDatabase[1]->AddEvent(-1 * 32, 24 * 32, "",[]
                                {
                                    LoadMap(3);
                                    Game::gPlayer->setPosition(59 * 32, 18 * 32);
                                });
    mapDatabase[1]->AddEvent(35 * 32, 30 * 32, "",[]
                                {
                                    LoadMap(4);
                                    Game::gPlayer->setPosition(27 * 32, 0 * 32);
                                });
    mapDatabase[1]->AddEvent(12 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});
    mapDatabase[1]->AddEvent(13 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});
    mapDatabase[1]->AddEvent(14 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});
    mapDatabase[1]->AddEvent(15 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});


    mapDatabase[1]->AddMonster(21*32,6*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(15*32,4*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(5*32,3*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(10*32,3*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(18*32,4*32,1,mapBase[1]);

    mapDatabase[1]->AddMonster(45*32,26*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(46*32,22*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(39*32,26*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(42*32,19*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(46*32,19*32,2,mapBase[1]);
}

void MapManager::LoadMap2()
{
    mapDatabase[2]->AddEvent(16 * 32, 20 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(10 * 32, 16 * 32);
                                });
    mapDatabase[2]->AddNPC(16 * 32, 9 * 32, "Sprite-Aurez", "Aurez Lv. 50");

}

void MapManager::LoadMap3()
{
    mapDatabase[3]->AddEvent(60 * 32, 17 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(0 * 32, 23 * 32);
                                });
    mapDatabase[3]->AddEvent(60 * 32, 18 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(0 * 32, 24 * 32);
                                });

}

void MapManager::LoadMap4()
{
    mapDatabase[4]->AddEvent(27 * 32, -1 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(35 * 32, 29 * 32);
                                });
    mapDatabase[4]->AddEvent(47 * 32, 20 * 32, "",[]
                                {
                                    LoadMap(5);
                                    Game::gPlayer->setPosition(16 * 32, 17 * 32);
                                });
}

void MapManager::LoadMap5()
{
    mapDatabase[5]->AddEvent(16 * 32, 18 * 32, "",[]
                                {
                                    LoadMap(4);
                                    Game::gPlayer->setPosition(47 * 32, 21 * 32);
                                });
     mapDatabase[5]->AddMonster(15 * 32, 6 * 32, 2, mapBase[5]);
}


void MapManager::OpenRankingBoard()
{
    if((Game::event.type == SDL_KEYDOWN))
    {
        switch(Game::event.key.keysym.sym )
        {
            case SDLK_LCTRL: Game::gRanking->showWindow(); break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
                Game::gRanking->hideWindow();
                break;
            default:
                break;
        }
    }
}
