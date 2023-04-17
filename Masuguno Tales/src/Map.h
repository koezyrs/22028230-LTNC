#pragma once

#ifndef Map_h
#define Map_h

#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include <iostream>
#include <queue>
#include <iomanip>

#include "Game.h"
#include "Actor.h"
#include "Monster.h"
#include "NPC.h"
#include "Wall.h"
#include "Projectile.h"
#include "Event.h"
#include "Tile.h"

#include "Vector2D.h"
#include "TextureManager.h"
#include "Settings.h"

// Database
#include "Database/MonsterDB.h"

class Map
{
public:
    Map(int _id);
    ~Map();
    int id;
    Tile** tiles;
    void setTargetAndCalculateFlowField(int targetXNew, int targetYNew);
    void calculateDistances();
    void calculateFlowDirections();
    void LoadMap(std::string maptex, const char* mapfile, int sizeX, int sizeY);
    void AddWall(int x, int y);
    void AddMonster(float x, float y, int monster_id);
    void AddEvent(float x, float y, std::function<void()> func = []{});
    void AddNPC(float x, float y, const char* filepath, std::string name);
    void AddProjectile(float x, float y, int frames, std::string skillName, float _damage);
    int getWidth();
    int getHeight();
    int getSizeX();
    int getSizeY();
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
