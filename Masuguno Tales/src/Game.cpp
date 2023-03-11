#include "Game.h"
#include "TextureManager.h"
#include "Component/Component.h"
#include "Map.h"
#include "MapManager.h"
#include "Collision.h"
#include "Entity.h"
#include "Actor.h"
#include "Monster.h"
#include "Settings.h"

#include "Window.h"
#include "Dialogue.h"


SDL_Event Game::event;
SDL_Renderer* Game::gRenderer = NULL;
SDL_Rect Game::gCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

Actor* Game::gPlayer;
Map* Game::currentMap;
Dialogue* testDialogue;

Game::Game(){};

Game::~Game(){};

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
    isRunning = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Unable to initialize SDL! SDL_Error: " << SDL_GetError() << endl;
        isRunning = false;
        return;
    }

    if(IMG_Init(IMG_INIT_PNG) < 0){
        cout << "Unable to initialize IMG! IMG_Error: " << IMG_GetError() << endl;
        isRunning = false;
        return;
    }

    if(TTF_Init() < 0){
        cout << "Unable to initialize TTF! TTF_Error: " << TTF_GetError() << endl;
        isRunning = false;
        return;
    }

    if(Mix_Init(MIX_INIT_OGG) < 0){
        cout << "Unable to initialize Mixer! Mix_Error: " << Mix_GetError() << endl;
        isRunning = false;
        return;
    }

    // Create window
    gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        cout << "Unable to create Window! SDL_Error: " << SDL_GetError() << endl;
        isRunning = false;
        return;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL){
        cout << "Unable to create Renderer! SDL_Error: " << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    return;
}

void Game::loadMedia()
{
    // Initialize Game Object Here
    gPlayer = new Actor(100, 100, "data files/graphics/player.png");
    currentMap = new Map();
    gPlayer->getTransformComponent()->position = Vector2D{15 * GAME_PIXELS, 1 * GAME_PIXELS};
    MapManager::LoadMap1();
    testDialogue = new Dialogue(static_cast<int>((SCREEN_WIDTH - 478)/2), static_cast<int>((SCREEN_HEIGHT - 240)/2), 478, 240, "Test Dialogue System");
    return;
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
        return;
    }
}

void Game::update()
{

    Vector2D playerPos = gPlayer->getTransformComponent()->position;

    // Update Game Object
    currentMap->Update();
    gPlayer->Update();

    // Collision check

    for(auto& wall : currentMap->walls)
    {
        if(Collision::AABB(*gPlayer->getColliderComponent(), *wall->getColliderComponent()))
        {
            gPlayer->getTransformComponent()->position = playerPos;
        }
    }

    for(auto& monster : currentMap->monsters)
    {
        if(Collision::AABB(*gPlayer->getColliderComponent(), *monster->getColliderComponent()))
        {
            gPlayer->getTransformComponent()->position = playerPos;
            monster->destroy();
        }
    }

    for(auto& eventa : currentMap->events)
    {
        if(Collision::AABB(*gPlayer->getColliderComponent(), *eventa->getColliderComponent()))
        {
            gPlayer->getTransformComponent()->position = playerPos;
            eventa->Perform();
        }
    }
    // Camera Update
    gCamera.x = gPlayer->getTransformComponent()->position.x - SCREEN_WIDTH / 2;
    gCamera.y = gPlayer->getTransformComponent()->position.y - SCREEN_HEIGHT / 2;
    if(gCamera.x < 0) gCamera.x = 0;
    if(gCamera.y < 0) gCamera.y = 0;
    if(gCamera.x >= gCamera.w) gCamera.x = gCamera.w;
    if(gCamera.y >= gCamera.h) gCamera.y = gCamera.h;
    if(gCamera.x + gCamera.w >= currentMap->getWidth()) gCamera.x = currentMap->getWidth() - gCamera.w;
    if(gCamera.y + gCamera.h >= currentMap->getHeight()) gCamera.y = currentMap->getHeight() - gCamera.h;

    return;
}

void Game::render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // Draw here
    currentMap->Refresh();
    currentMap->Render();
    gPlayer->Render();
    testDialogue->Render();
    // Update screen
    SDL_RenderPresent(gRenderer);

    return;
}


bool Game::running()
{
    return isRunning;
}

void Game::clean()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    gWindow = NULL;
    gRenderer = NULL;

    delete gPlayer;
    delete currentMap;
    delete testDialogue;
    cout << "Game cleaned" << endl;

    return;
}
