#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Component/Component.h"
#include "../include/GameEnity/GameEntity.h"
#include "../include/Map.h"
#include "../include/Collision.h"
#include "../include/Entity.h"
#include "../include/GameActor.h"
#include "../include/config.h"

SDL_Renderer* Game::gRenderer = NULL;
SDL_Event Game::event;

std::vector<TileEntity*> Game::gGroupMap;
std::vector<GameActor*> Game::gGroupPlayers;
std::vector<ColliderComponent*> Game::gGroupColliders;


GameActor* gPlayer;

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

    // Init Game Object Here
    gPlayer = new GameActor();
    Map::LoadMap("assets/map_16x16.msgn", 16, 16);
    return;
}

void Game::loadMedia()
{
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
    // Update Game Object
    for(auto e : gGroupMap)
    {
        e->Update();
    }

    for(auto e: gGroupPlayers)
    {
        e->Update();
    }

    // Collision check
    for(auto cc : gGroupColliders)
    {
        Collision::AABB(*gPlayer->getColliderComponent(), *cc);
    }
    return;
}

void Game::render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // Draw here
    for(auto e : gGroupMap)
    {
        e->Render();
    }

    for(auto e: gGroupPlayers)
    {
        e->Render();
    }
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

void Game::AddTile(int id, int x, int y, std::string tag)
{
    TileEntity* tile = new TileEntity(id, x, y, tag);
    return;
}
