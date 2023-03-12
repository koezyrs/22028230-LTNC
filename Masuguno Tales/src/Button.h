#pragma once
#ifndef Button_h
#define Button_h
#include <SDL.h>
#include <functional>
#include "Vector2D.h"
#include "Window.h"

class Button
{
public:
    Button(const char* spriteOut, const char* spriteOver, int x, int y, int _width, int _height, std::function<void()> func = []{});
    ~Button();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void Render();
    void Perform();
private:
    bool inside = false;
    Vector2D position;
    int Width, Height;
    std::function<void()> ButtonFunction;
    SDL_Rect srcRect, destRect;
    SDL_Texture* ButtonSpriteOut;
    SDL_Texture* ButtonSpriteOver;
};


#endif // Button_h
