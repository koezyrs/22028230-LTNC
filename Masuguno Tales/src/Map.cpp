#include <string>
#include <fstream>
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/TextureManager.h"

Map::Map()
{

};

Map::~Map()
{

};

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    std::fstream mapfile;
    char tile;
    std::string tag;

    mapfile.open(path);
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0 ; x < sizeX; x++)
        {
            mapfile.get(tile);
            int id = atoi(&tile);
            if(id == 0) tag = "Dirt";
            else if(id == 1) tag = "Grass";
            else if(id == 2) tag = "Water";
            Game::AddTile(id, x * GAME_PIXELS, y * GAME_PIXELS, tag);
            mapfile.ignore();
        }
    }
    mapfile.close();
}

void Map::Update()
{

}

void Map::Render()
{

}


