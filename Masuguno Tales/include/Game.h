#pragma once
#ifndef Game_h
#define Game_h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "config.h"

using namespace std;

class Game{
public:
    Game();
    ~Game();
    void init(const char* titile, int xpos, int ypos, int width, int height);
    void loadMedia();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
private:
    bool isRunning;
    SDL_Window* gWindow;
};
#endif // Game_h
