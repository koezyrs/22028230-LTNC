// System Include
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "MapManager.h"
#include "Collision.h"
#include "Entity.h"
#include "Actor.h"
#include "Monster.h"
#include "Item.h"
#include "Equipment.h"

// GUI Include
#include "Window.h"
#include "Dialogue.h"
#include "DialogueManager.h"
#include "Inventory.h"
#include "CharacterInformation.h"
#include "HUD.h"
#include "Hotbar.h"

// Database
#include "Database/MonsterDB.h"
#include "Database/SkillDB.h"

// Settings
#include "Settings.h"

SDL_Event Game::event;
SDL_Renderer* Game::gRenderer = NULL;
SDL_Rect Game::gCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

Actor* Game::gPlayer;
Map* Game::currentMap;
Dialogue* Game::gDialogue;
Inventory* Game::gInventory;
HUD* Game::gHUD;
Hotbar* Game::gHotbar;
CharacterInformation* Game::gCharacterInformation;

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
    srand(time(0));
    return;
}

void Game::loadResources()
{
    // GUI
    TextureManager::LoadTexture("data files/graphics/gui/8.png", "CloseButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/9.png", "CloseButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/Dialogue.png", "Dialogue");
    TextureManager::LoadTexture("data files/graphics/gui/CharacterInformation.png", "CharacterInformation");
    TextureManager::LoadTexture("data files/graphics/gui/Hotbar.png", "Hotbar");
    TextureManager::LoadTexture("data files/graphics/gui/HUDBars.png", "HUDBars");
    TextureManager::LoadTexture("data files/graphics/gui/HUDBase.png", "HUDBase");
    TextureManager::LoadTexture("data files/graphics/gui/Inventory.png", "Inventory");
    TextureManager::LoadTexture("data files/graphics/gui/Quest.png", "Quest");
    TextureManager::LoadTexture("data files/graphics/gui/HPBar.png", "HPBar");
    TextureManager::LoadTexture("data files/graphics/gui/Target.png", "Target");
    TextureManager::LoadTexture("data files/graphics/gui/TargetHPBar.png", "TargetHPBar");
    TextureManager::LoadTexture("data files/graphics/gui/48.png", "AddButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/49.png", "AddButtonOver");

    // Map
    TextureManager::LoadTexture("data files/maps/map01.png", "Map01");
    TextureManager::LoadTexture("data files/maps/map02.png", "Map02");

    // Sprite
    TextureManager::LoadTexture("data files/graphics/player.png", "Sprite-Player");
    TextureManager::LoadTexture("data files/graphics/characters/158.png", "Sprite-Guard1");
    TextureManager::LoadTexture("data files/graphics/characters/159.png", "Sprite-Guard2");
    TextureManager::LoadTexture("data files/graphics/characters/17.png", "Sprite-MonsterCow");

    //Equipment
    TextureManager::LoadTexture("data files/graphics/items/2.png", "Equip-AssasinDagger");

    // Item
    TextureManager::LoadTexture("data files/graphics/items/14.png", "Item-HPPotion");

    // Faces
    TextureManager::LoadTexture("data files/graphics/faces/18.png", "Face-Guard1");

    // Skill
    TextureManager::LoadTexture("data files/graphics/animations/13.png", "Skill-Basic Attack");
}

void Game::loadData()
{
    // Initialize Game Object Here
    currentMap = new Map();
    gPlayer = new Actor(100, 100, "Sprite-Player");

    // Initialize GUI
    gDialogue = new Dialogue((SCREEN_WIDTH - 478)/2 , (SCREEN_HEIGHT - 226)/2, 478, 226, " ", "EmptyFace", " ");
    gInventory = new Inventory(790, 130, 198, 314);
    gCharacterInformation = new CharacterInformation(50,110, 206, 418);
    gHUD = new HUD();
    gHotbar = new Hotbar();

    // Load all game dialogue
    DialogueManager::LoadDialogue();

    // Load all monster types
    MonsterDB::LoadMonsterDatabase();

    // Load all skill types
    SkillDB::LoadSkillDatabase();

    // Load all item types
    ItemDB::LoadItemDatabase();

    // Load all equipment types
    EquipmentDB::LoadEquipmentDatabase();

    // Load the begin map
    MapManager::LoadMap1();

    // Set player position
    gPlayer->getTransformComponent()->position = Vector2D{15 * GAME_PIXELS, 10 * GAME_PIXELS};

    // Add test Item
    gInventory->AddEquipment(1);
    for(int i = 0; i < 40; i ++) gInventory->AddItem(1);

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
                Game::gCharacterInformation->hideWindow();
                break;
            case SDLK_i:
                Game::gInventory->Toggle();
                break;
            case SDLK_c:
                Game::gCharacterInformation->Toggle();
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
    gHUD->Update();
    gHotbar->Update();
    if(!gDialogue->isHide()) gDialogue->Update();
    if(!gInventory->isHide()) gInventory->Update();
    if(!gCharacterInformation->isHide()) gCharacterInformation->Update();

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

        float exitDistance = 1.0f;
        if((Game::event.type == SDL_KEYDOWN) && (distance <= GAME_PIXELS + exitDistance))
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
                    case SDLK_LCTRL: npc->PlayDialogue();
                }
            }
        }

        if((distance > GAME_PIXELS + 1) && (npc->isInteract)) npc->HideDialogue();

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

    // Apply damage from projectile
    for(auto& prjtile : currentMap->projectiles)
    {
        if(prjtile->isUsed()) continue;
        for(auto& mon : currentMap->monsters)
        {
            if(prjtile->getTag() == "Monster") continue;
            if(Collision::AABB(*prjtile->getColliderComponent(), *mon->getColliderComponent()))
            {
                mon->ApplyDamage(prjtile->getDamage());
                prjtile->Used();
            }
        }

        if(prjtile->getTag() == "Player") continue;
        if(Collision::AABB(*prjtile->getColliderComponent(), *Game::gPlayer->getColliderComponent()))
        {
            Game::gPlayer->mStats->ApplyDamage(prjtile->getDamage());
            prjtile->Used();
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
    if(!gCharacterInformation->isHide()) gCharacterInformation->Render();
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
    TextureManager::CleanTexture();
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
    delete gCharacterInformation;

    cout << "Game cleaned" << endl;

    return;
}
