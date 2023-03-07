#include <string>
#include <fstream>
#include <algorithm>
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include "../include/config.h"

Map::Map(const char* maptex, const char* mapfile, int sizeX, int sizeY)
{
    LoadMap(maptex, mapfile, sizeX, sizeY);
};

Map::~Map()
{
    ClearMap();
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

void Map::Refresh()
{
    walls.erase(std::remove_if(walls.begin(), walls.end(),
        [](const std::unique_ptr<Wall>& theWall){return !theWall->isActive();}), walls.end());

    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](const std::unique_ptr<Monster>& theMonster){return !theMonster->isActive();}), monsters.end());
}

void Map::Update()
{
    destRect.x = position.x - Game::gCamera.x;
    destRect.y = position.y - Game::gCamera.y;

    for(auto& w : walls)
    {
        w->Update();
    }

    for(auto& m : monsters)
    {
        m->Update();
    }
}

void Map::Render()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
    for(auto& m : monsters)
    {
        m->Render();
    }
}

void Map::AddWall(int x, int y)
{
    std::unique_ptr<Wall> newWall(new Wall(static_cast<float>(x), static_cast<float>(y)));
    walls.push_back(std::move(newWall));
}

void Map::AddMonster(float x, float y, const char* filepath)
{
    std::unique_ptr<Monster> newMonster(new Monster(x, y, GAME_PIXELS, GAME_PIXELS, 1, filepath));
    monsters.push_back(std::move(newMonster));
}

void Map::ClearMap()
{
    walls.erase(walls.begin(), walls.end());
    monsters.erase(monsters.begin(), monsters.end());
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}
