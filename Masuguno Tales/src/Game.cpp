#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Map.h"
#include "../include/Collision.h"
#include "../include/GameActor.h"
#include "../include/Wall.h"
#include "../include/config.h"

GameActor* gPlayer;
Wall* testWall;
Map* currentMap;
SDL_Renderer* Game::gRenderer = NULL;
SDL_Event Game::event;

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
    gPlayer = new GameActor();
    testWall = new Wall();
    currentMap = new Map();
    return;
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }

    return;
}

void Game::update()
{
    gPlayer->Update();
    testWall->Update();
    if (Collision::AABB(gPlayer->getColliderComponent()->collider,
                       testWall->getColliderComponent()->collider))
    {
        gPlayer->getTransformComponent()->scale = 1;
        cout << "Hit Wall!!!" << endl;
    }
    return;
}

void Game::render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // Draw here
    currentMap->DrawMap();
    gPlayer->Render();
    testWall->Render();

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

    cout << "Game cleaned" << endl;

    return;
}
