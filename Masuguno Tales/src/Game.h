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
#include "Settings.h"

class Map;
class Actor;
class Dialogue;
class Inventory;
class CharacterInformation;
class HUD;
class Hotbar;

using namespace std;

class Game{
public:
    Game();
    ~Game();
    void init(const char* titile, int xpos, int ypos, int width, int height);
    void loadResources();
    void loadData();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    static SDL_Event event;
    static SDL_Renderer* gRenderer;

    static Map* currentMap;
    static Actor* gPlayer;
    static Dialogue* gDialogue;
    static Inventory* gInventory;
    static CharacterInformation* gCharacterInformation;
    static HUD* gHUD;
    static Hotbar* gHotbar;

    static SDL_Rect gCamera;
private:
    bool isRunning;
    SDL_Window* gWindow;

};
#endif // Game_h
