#include "../include/Map.h"
#include "../include/TextureManager.h"

int lv1[20][25] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,2,0,0,0,0,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,0,2,0,0,0,0,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map()
{
    dirt = TextureManager::LoadTexture("assets/dirt.png");
    grass = TextureManager::LoadTexture("assets/grass.png");
    water = TextureManager::LoadTexture("assets/water.png");

    LoadMap(lv1);
};
Map::~Map(){};

void Map::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            GameMap[row][column] = arr[row][column];
        }
    }
    srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
    srcRect.w = srcRect.h = destRect.w = destRect.h = 32;
}

void Map::DrawMap()
{
    int type = 0;
    for (int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            type = GameMap[row][column];
            destRect.x = column * 32;
            destRect.y = row * 32;
            switch(type)
            {
            case 0:
                TextureManager::Draw(water, srcRect, destRect);
                break;
            case 1:
                TextureManager::Draw(grass, srcRect, destRect);
                break;
            case 2:
                TextureManager::Draw(dirt, srcRect, destRect);
                break;
            default:
                break;
            }
        }
    }
}

