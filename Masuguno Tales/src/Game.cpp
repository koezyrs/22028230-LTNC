// System Include
#include <math.h>
#include "Game.h"
#include "TextureManager.h"
#include "Component/Component.h"
#include "Settings.h"
#include "Map.h"
#include "MapManager.h"
#include "Collision.h"
#include "Entity.h"
#include "Actor.h"
#include "Monster.h"
#include "Item.h"

// GUI Include
#include "Window.h"
#include "Dialogue.h"
#include "DialogueManager.h"
#include "Inventory.h"
#include "HUD.h"
#include "Hotbar.h"

SDL_Event Game::event;
SDL_Renderer* Game::gRenderer = NULL;
SDL_Rect Game::gCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

Actor* Game::gPlayer;
Map* Game::currentMap;
Dialogue* Game::gDialogue;
Inventory* Game::gInventory;
HUD* Game::gHUD;
Hotbar* Game::gHotbar;

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

void Game::loadData()
{
    // Initialize Game Object Here
    currentMap = new Map();
    gPlayer = new Actor(100, 100, "data files/graphics/player.png");

    // Initialize GUI
    gDialogue = new Dialogue((SCREEN_WIDTH - 478)/2 , (SCREEN_HEIGHT - 226)/2, 478, 226, "a", "data files/graphics/faces/1.png", "a");
    gInventory = new Inventory(790, 130, 198, 314);
    gHUD = new HUD();
    gHotbar = new Hotbar();

    // Load all game dialogue
    DialogueManager::LoadDialogue();

    // Load the begin map
    MapManager::LoadMap1();

    // Set player position
    gPlayer->getTransformComponent()->position = Vector2D{15 * GAME_PIXELS, 10 * GAME_PIXELS};

    // Add test Item
    gInventory->AddItem(new Item(1,"data files/graphics/items/2.png",1,"Dagger", "Assasin Dagger", []{}) );
    gInventory->AddItem(new Item(2,"data files/graphics/items/3.png",1,"Sword", "Masuguno Sword", []{}) );
    gInventory->AddItem(new Item(3,"data files/graphics/items/4.png",1,"Axe1", "Draven Axe", []{}) );
    gInventory->AddItem(new Item(4,"data files/graphics/items/5.png",1,"Axe2", "Darius Axe", []{}) );
    gInventory->AddItem(new Item(5,"data files/graphics/items/6.png",1,"Helmet", "Supierior Helmet", []{}) );
    gInventory->AddItem(new Item(6,"data files/graphics/items/7.png",1,"Armo", "Dragon Armor", []{}) );
    gInventory->AddItem(new Item(7,"data files/graphics/items/8.png",1,"Cloack", "Mystic Cloack", []{}) );
    gInventory->AddItem(new Item(8,"data files/graphics/items/9.png",1,"Boots", "Water Boots", []{}) );
    gInventory->AddItem(new Item(9, "data files/graphics/items/14.png", 5, "Potion", "HP Potion", []{if(gPlayer->mStats->getHealth() + 10 <= gPlayer->mStats->getMaxHealth()) gPlayer->mStats->setHealth(gPlayer->mStats->getHealth() + 10);}));
    gInventory->AddItem(new Item(10, "data files/graphics/items/12.png", 5, "Potion", "MP Potion", []{if(gPlayer->mStats->getMana() + 10 <= gPlayer->mStats->getMaxMana()) gPlayer->mStats->setMana(gPlayer->mStats->getMana() + 10);}));
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

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Game::gDialogue->hideWindow();
                Game::gInventory->hideWindow();
                break;
            case SDLK_i:
                Game::gInventory->Toggle();
                break;
            default:
                break;
            }
        }
        return;
    }

}

void Game::update()
{
    // Saved the last position after taking the next move
    Vector2D playerPos = gPlayer->getTransformComponent()->position;

    // Update Game Object
    currentMap->Update();
    gPlayer->Update();
    if(!gDialogue->isHide()) gDialogue->Update();
    if(!gInventory->isHide()) gInventory->Update();
    gHUD->Update();
    gHotbar->Update();

    // Collision check
    for(auto& wall : currentMap->walls)
    {
        if(Collision::AABB(*gPlayer->getColliderComponent(), *wall->getColliderComponent()))
        {
            gPlayer->getTransformComponent()->position = playerPos;
        }
    }

    // Hit Monster check
    for(auto& monster : currentMap->monsters)
    {
        if(Collision::AABB(*gPlayer->getColliderComponent(), *monster->getColliderComponent()))
        {
            gPlayer->getTransformComponent()->position = playerPos;
            monster->destroy();
        }
    }

    // Collide with NPC
    for(auto& npc : currentMap->npcs)
    {
        // Check Collision
        if(Collision::AABB(*gPlayer->getColliderComponent(), *npc->getColliderComponent()))
        {
            gPlayer->getTransformComponent()->position = playerPos;
        }

        // Interact with NPC
        Vector2D npcPos = npc->getTransformComponent()->position;
        Vector2D currentplayerPos = gPlayer->getTransformComponent()->position;
        float distance = sqrt((npcPos.x - currentplayerPos.x)*(npcPos.x - currentplayerPos.x) + (npcPos.y - currentplayerPos.y)*(npcPos.y - currentplayerPos.y));

        if((Game::event.type == SDL_KEYDOWN) && (distance <= GAME_PIXELS + 1))
        {
            // Check if NPC and Player are facing to each other
            int playerAnimIndex = gPlayer->getSpriteComponent()->animIndex;
            int npcAnimIndex = npc->getSpriteComponent()->animIndex;
            bool success = false;
            if(playerAnimIndex == 0 && npcAnimIndex == 3) success = true;
            else if(playerAnimIndex == 1 && npcAnimIndex == 2) success = true;
            else if(playerAnimIndex == 2 && npcAnimIndex == 1) success = true;
            else if(playerAnimIndex == 3 && npcAnimIndex == 0) success = true;

            // If is facing
            if(success){
                switch(Game::event.key.keysym.sym )
                {
                    case SDLK_LCTRL: {npc->PlayDialogue(); npc->isInteract = true;}
                }
            }
        }

        if((distance > GAME_PIXELS + 1) && (npc->isInteract)) {npc->HideDialogue(); npc->isInteract = false;}

    }

    // Interact with event
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
    currentMap->RenderBottomLayer();
    gPlayer->Render();
    currentMap->RenderUpperLayer();

    if(!gDialogue->isHide()) gDialogue->Render();
    if(!gInventory->isHide()) gInventory->Render();
    gHUD->Render();
    gHotbar->Render();

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

    delete currentMap;
    delete gPlayer;
    delete gDialogue;
    delete gInventory;
    delete gHUD;
    delete gHotbar;

    cout << "Game cleaned" << endl;

    return;
}
