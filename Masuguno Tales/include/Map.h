#pragma once

#ifndef Map_h
#define Map_h
#include "Game.h"
class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();
private:
    SDL_Rect srcRect, destRect;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    int GameMap[20][25];

};

#endif // Map_h
