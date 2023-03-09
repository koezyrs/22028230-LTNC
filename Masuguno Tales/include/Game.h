#pragma once
#ifndef Game_h
#define Game_h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include "Config.h"

class Map;
class Entity;
class Actor;
class ColliderComponent;

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

    static SDL_Event event;
    static SDL_Renderer* gRenderer;
    static Actor* gPlayer;
    static Map* currentMap;
    static SDL_Rect gCamera;
private:
    bool isRunning;
    SDL_Window* gWindow;

};
#endif // Game_h
