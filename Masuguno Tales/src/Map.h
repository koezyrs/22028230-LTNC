#pragma once

#ifndef Map_h
#define Map_h

#include<string>
#include<vector>
#include <memory>
#include "Vector2D.h"
#include "Wall.h"
#include "Monster.h"
#include "Event.h"
#include "NPC.h"

class Map
{
public:
    Map();
    void LoadMap(const char* maptex, const char* mapfile, int sizeX, int sizeY);
    void AddWall(int x, int y);
    void AddMonster(float x, float y, const char* filepath, std::string name);
    void AddEvent(Event* newEvent);
    void AddNPC(float x, float y, const char* filepath, std::string name);
    int getWidth() {return width;}
    int getHeight() {return height;}
    void ClearMap();
    void Refresh();
    void Update();
    void RenderBottomLayer();
    void RenderUpperLayer();
    ~Map();
    std::vector<Event*> events;
    std::vector<Wall*> walls;
    std::vector<Monster*> monsters;
    std::vector<NPC*> npcs;
private:
    int width;
    int height;
    Vector2D position;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;
};

#endif // Map_h
