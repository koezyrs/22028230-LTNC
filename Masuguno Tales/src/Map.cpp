#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
#include "Settings.h"
#include "Event/EventType.h"
Map::Map()
{
    LoadMap("data files/maps/map01.png", "data files/maps/map02.msgn", 30, 35);
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
            if(id == 1) AddWall(x * GAME_PIXELS * GAME_SCALE, y * GAME_PIXELS * GAME_SCALE);
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

    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](NPC* theNPC) {return !theNPC->isActive();}), npcs.end());

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

    for(auto& n : npcs)
    {
        n->Update();
    }

    for(auto& e : events)
    {
        e->Update();
    }
}

void Map::RenderBottomLayer()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
}

void Map::RenderUpperLayer()
{
    for(auto& m : monsters)
    {
        m->Render();
    }

    for(auto& n : npcs)
    {
        n->Render();
    }
}
void Map::AddWall(int x, int y)
{
    walls.emplace_back(new Wall(static_cast<float>(x), static_cast<float>(y)));
}

void Map::AddMonster(float x, float y, const char* filepath, std::string name)
{
    monsters.emplace_back(new Monster(x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE, filepath, name));
}

void Map::AddEvent(Event* newEvent)
{
    events.emplace_back(newEvent);
}

void Map::AddNPC(float x, float y, const char* filepath, std::string name)
{
    npcs.emplace_back(new NPC(x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE, filepath, name));
}

void Map::ClearMap()
{
    for(auto& w : walls) {w->destroy();}
    for(auto& m : monsters) {m->destroy();}
    for(auto& e : events) {e->destroy();}
    for(auto& n : npcs) (n->destroy());
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    Refresh();
}
