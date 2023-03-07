#pragma once

#ifndef Map_h
#define Map_h

#include<string>
#include<vector>
#include "Vector2D.h"
#include "Wall.h"

class Map
{
public:
    Map(const char* maptex, const char* mapfile, int sizeX, int sizeY);
    void LoadMap(const char* maptex, const char* mapfile, int sizeX, int sizeY);
    void AddWall(int x, int y);
    int getWidth() {return width;}
    int getHeight() {return height;}
    void ClearMap();
    void Update();
    void Render();
    ~Map();
private:
    int width;
    int height;
    Vector2D position;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;
    vector<Wall*> walls;
};

#endif // Map_h
