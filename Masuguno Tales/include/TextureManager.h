#pragma once

#ifndef TextureManager_h
#define TextureManager_h

#include "Game.h"
class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
};



#endif // TextureManager_h
