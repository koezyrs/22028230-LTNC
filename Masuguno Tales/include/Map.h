#pragma once

#ifndef Map_h
#define Map_h

#include<string>
#include<vector>
#include <memory>
#include "Vector2D.h"
#include "Wall.h"
#include "Monster.h"

class Map
{
public:
    Map(const char* maptex, const char* mapfile, int sizeX, int sizeY);
    void LoadMap(const char* maptex, const char* mapfile, int sizeX, int sizeY);
    void AddWall(int x, int y);
    void AddMonster(float x, float y, const char* filepath);
    int getWidth() {return width;}
    int getHeight() {return height;}
    void ClearMap();
    void Refresh();
    void Update();
    void Render();
    ~Map();
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Monster>> monsters;
private:
    int width;
    int height;
    Vector2D position;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;
};

#endif // Map_h
