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
#include "config.h"

class ColliderComponent;
class Entity;
class GameActor;
class TileEntity;

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

    static void AddTile(int id, int x, int y, std::string tag);
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    static std::vector<TileEntity*> gGroupMap;
    static std::vector<GameActor*> gGroupPlayers;
    //static std::vector<EnemyActor*> gGroupEnemies;
    static std::vector<ColliderComponent*> gGroupColliders;
private:
    bool isRunning;
    SDL_Window* gWindow;
};
#endif // Game_h
