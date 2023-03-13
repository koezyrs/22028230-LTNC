#pragma once
#ifndef Label_h
#define Label_h

#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector2D.h"
#include <functional>

class Label
{
public:
    Label(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor, Uint32 wrapLength, bool isFunc = false , std::function<void()> func = []{});
    ~Label();
    void handleEvent(SDL_Event* e);
    void Render();
    void Perform();
    void Reset();
private:
    bool isFunctional = false;
    bool inside = false;
    Vector2D position;
    int Width, Height;
    std::function<void()> LabelFunction;
    SDL_Rect srcRect, destRect;
    SDL_Texture* textOut;
    SDL_Texture* textOver;
    TTF_Font* font;
};

#endif // Label_h
