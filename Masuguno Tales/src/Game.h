#pragma once
#ifndef Game_h
#define Game_h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>
#include "Settings.h"

class Login;
class Map;
class Actor;
class Dialogue;
class Inventory;
class CharacterInformation;
class HUD;
class Hotbar;
class QuestLog;

using namespace std;

enum SESSION_GAME
    {
        INIT,
        LOAD_RESOURCES,
        LOGIN,
        LOAD_DATA,
        RUNNING,
        SAVE_DATA,
        CLEAR
    };

class Game{
public:
    Game();
    ~Game();
    void init(const char* titile, int xpos, int ypos, int width, int height);
    void loadResources();
    void loginProcess();
    void loadData();
    void handleEvents();
    void update();
    void render();
    void saveData();
    void clean();

    static SDL_Event event;
    static SDL_Renderer* gRenderer;

    static MYSQL* conn;
    static Map* currentMap;
    static Actor* gPlayer;
    static Dialogue* gDialogue;
    static Inventory* gInventory;
    static CharacterInformation* gCharacterInformation;
    static HUD* gHUD;
    static Hotbar* gHotbar;
    static QuestLog* gQuestLog;

    static SDL_Rect gCamera;
    static SESSION_GAME session;
private:
    SDL_Window* gWindow;
    Login* loginPanel;

};
#endif // Game_h
