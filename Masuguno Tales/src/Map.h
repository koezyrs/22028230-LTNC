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
#include "Tile.h"
#include "Projectile.h"

class Map
{
public:
    Map();
    ~Map();
    Tile** tiles;
    void setTargetAndCalculateFlowField(int targetXNew, int targetYNew);
    void calculateDistances();
    void calculateFlowDirections();
    void LoadMap(std::string maptex, const char* mapfile, int sizeX, int sizeY);
    void AddWall(int x, int y);
    void AddMonster(float x, float y, const char* filepath, std::string name, float _speed);
    void AddEvent(Event* newEvent);
    void AddNPC(float x, float y, const char* filepath, std::string name);
    void AddProjectile(float x, float y);
    int getWidth() {return width;}
    int getHeight() {return height;}
    int getSizeX() {return sizeX;}
    int getSizeY() {return sizeY;}
    void ClearMap();
    void Refresh();
    void Update();
    void RenderBottomLayer();
    void RenderUpperLayer();
    std::vector<Event*> events;
    std::vector<Wall*> walls;
    std::vector<Monster*> monsters;
    std::vector<NPC*> npcs;
    std::vector<Projectile*> projectiles;
private:
    int width;
    int height;
    int sizeX;
    int sizeY;
    int targetX;
    int targetY;
    Vector2D position;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;
};

#endif // Map_h
