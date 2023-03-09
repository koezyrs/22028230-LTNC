#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include "../include/Config.h"
#include "../include/Event/EventType.h"
Map::Map()
{
    LoadMap("assets/map01.png", "assets/map01.msgn", 30, 35);
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
        [](Wall* theWall){return !theWall->isActive();}), walls.end());

    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](Monster* theMonster){return !theMonster->isActive();}), monsters.end());

    events.erase(std::remove_if(events.begin(), events.end(),
        [](Event* theEvent){return !theEvent->isActive();}), events.end());
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

    for(auto& e : events)
    {
        e->Update();
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
    walls.emplace_back(new Wall(static_cast<float>(x), static_cast<float>(y)));
}

void Map::AddMonster(float x, float y, const char* filepath)
{
    monsters.emplace_back(new Monster(x, y, GAME_PIXELS, GAME_PIXELS, 1, filepath));
}

void Map::AddEvent(Event* newEvent)
{
    events.emplace_back(newEvent);
    std::cout << "Added new Event!" << endl;
}

void Map::ClearMap()
{
    for(auto& w: walls) {w->destroy();}
    for(auto& m : monsters) {m->destroy();}
    for(auto& e : events) {e->destroy();}
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}
