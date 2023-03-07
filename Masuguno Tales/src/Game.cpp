#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Component/Component.h"
#include "../include/Map.h"
#include "../include/Collision.h"
#include "../include/Entity.h"
#include "../include/GameActor.h"
#include "../include/Monster.h"
#include "../include/config.h"

SDL_Event Game::event;
SDL_Renderer* Game::gRenderer = NULL;
SDL_Rect Game::gCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

std::vector<ColliderComponent*> Game::gGroupColliders;


GameActor* Game::gPlayer;
Map* Game::currentMap;

Monster* gCow;

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

    // Initialize Game Object Here
    gPlayer = new GameActor();
    currentMap = new Map("assets/map01.png", "assets/map01.msgn", 35, 30);
    gCow = new Monster(300, 300, GAME_PIXELS,GAME_PIXELS, 1, "assets/cow.png");
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

    Vector2D playerPos = gPlayer->getTransformComponent()->position;

    // Update Game Object
    currentMap->Update();
    gPlayer->Update();

    gCow->Update();
    // Collision check
    for(auto& cc : gGroupColliders)
    {
        SDL_Rect playerCol = gPlayer->getColliderComponent()->mCollider;
        SDL_Rect cCol = cc->mCollider;
        if((Collision::AABB(playerCol, cCol)) && (cc->tag == "Wall"))
        {
            gPlayer->getTransformComponent()->position = playerPos;
        }

        if((Collision::AABB(playerCol, cCol)) && (cc->tag == "Monster"))
        {
            gPlayer->getTransformComponent()->position = playerPos;
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
    currentMap->Render();
    gPlayer->Render();

    gCow->Render();
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
