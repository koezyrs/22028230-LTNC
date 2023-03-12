#pragma once
#ifndef Label_h
#define Label_h

#include <SDL_ttf.h>
#include "Vector2D.h"

class Label
{
public:
    Label(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor);
    ~Label();
    void Render();
private:
    Vector2D position;
    int Width, Heigth;
    SDL_Rect srcRect, destRect;
    SDL_Texture* text;
    TTF_Font* font;
};

#endif // Label_h
