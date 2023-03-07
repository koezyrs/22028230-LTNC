#include <string>
#include <fstream>
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/TextureManager.h"

Map::Map(const char* maptex, const char* mapfile, int sizeX, int sizeY)
{
    LoadMap(maptex, mapfile, sizeX, sizeY);
};

Map::~Map()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }
};

void Map::LoadMap(const char* maptex, const char* mapfile, int sizeX, int sizeY)
{
    mTexture = TextureManager::LoadTexture(maptex);
    SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);
    srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    position.x = 0.0f;
    position.y = 0.0f;

    std::fstream fileContainCoordiate;
    char tile;

    fileContainCoordiate.open(mapfile);
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0 ; x < sizeX; x++)
        {
            fileContainCoordiate.get(tile);
            int id = atoi(&tile);
            if(id == 1) AddWall(x * GAME_PIXELS, y * GAME_PIXELS);
            fileContainCoordiate.ignore();
        }
    }
    fileContainCoordiate.close();
}

void Map::Update()
{
    destRect.x = position.x - Game::gCamera.x;
    destRect.y = position.y - Game::gCamera.y;

    for(auto& w : walls)
    {
        w->Update();
    }

}

void Map::Render()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
}

void Map::AddWall(int x, int y)
{
    Wall* newWall = new Wall(static_cast<float>(x), static_cast<float>(y));
    walls.push_back(newWall);
}

void Map::ClearMap()
{
    for(auto& w : walls)
    {
        delete w;
    }
    walls.erase(walls.begin(), walls.end());

    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}
