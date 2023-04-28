// System Include
#include <math.h>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Login/Login.h"
#include "Register/Register.h"
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
#include "QuestLog.h"
#include "Shop.h"

// Database
#include "Database/MonsterDB.h"
#include "Database/SkillDB.h"
#include "Database/EquipmentDB.h"
#include "Database/ItemDB.h"
#include "Database/QuestDB.h"
#include "Database/ShopDB.h"

// Settings
#include "Settings.h"

SESSION_GAME Game::session;
MYSQL* Game::conn;
SDL_Event Game::event;
SDL_Renderer* Game::gRenderer;
SDL_Rect Game::gCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

std::shared_ptr<Map> Game::currentMap;
std::unique_ptr<Actor> Game::gPlayer;
std::unique_ptr<Dialogue> Game::gDialogue;
std::unique_ptr<Inventory> Game::gInventory;
std::unique_ptr<HUD> Game::gHUD;
std::unique_ptr<Hotbar> Game::gHotbar;
std::unique_ptr<CharacterInformation> Game::gCharacterInformation;
std::unique_ptr<QuestLog> Game::gQuestLog;
std::unique_ptr<Shop> Game::gShop;

Game::Game() {
    session = INIT;
};

Game::~Game(){};

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Unable to initialize SDL! SDL_Error: " << SDL_GetError() << endl;
        session = CLEAR;
        return;
    }

    if(IMG_Init(IMG_INIT_PNG) < 0){
        cout << "Unable to initialize IMG! IMG_Error: " << IMG_GetError() << endl;
        session = CLEAR;
        return;
    }

    if(TTF_Init() < 0){
        cout << "Unable to initialize TTF! TTF_Error: " << TTF_GetError() << endl;
        session = CLEAR;
        return;
    }

    if(Mix_Init(MIX_INIT_OGG) < 0){
        cout << "Unable to initialize Mixer! Mix_Error: " << Mix_GetError() << endl;
        session = CLEAR;
        return;
    }

    // Create window
    gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        cout << "Unable to create Window! SDL_Error: " << SDL_GetError() << endl;
        session = CLEAR;
        return;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL){
        cout << "Unable to create Renderer! SDL_Error: " << SDL_GetError() << endl;
        session = CLEAR;
        return;
    }
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    srand(time(0));

    session = LOAD_RESOURCES;
    return;
}

void Game::loadResources()
{
    // GUI
    TextureManager::LoadTexture("data files/graphics/gui/Login.png", "Login");
    TextureManager::LoadTexture("data files/graphics/gui/LoginButtonOut.png", "LoginButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/LoginButtonOver.png", "LoginButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/ExitButtonOut.png", "ExitButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/ExitButtonOver.png", "ExitButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/Register.png", "Register");
    TextureManager::LoadTexture("data files/graphics/gui/RegistButtonOut.png", "RegistButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/RegistButtonOver.png", "RegistButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/BackButtonOut.png", "BackButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/BackButtonOver.png", "BackButtonOver");
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
    TextureManager::LoadTexture("data files/graphics/gui/Shop.png", "Shop");
    TextureManager::LoadTexture("data files/graphics/gui/AcceptButtonOut.png", "AcceptButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/AcceptButtonOver.png", "AcceptButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/58.png", "BuyButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/56.png", "BuyButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/59.png", "SellButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/57.png", "SellButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/DescriptionBox.png", "DescriptionBox");

    // Map
    TextureManager::LoadTexture("data files/maps/map01.png", "Map01");
    TextureManager::LoadTexture("data files/maps/map01_above_player.png", "Map01_Overlay");
    TextureManager::LoadTexture("data files/maps/map02.png", "Map02");
    TextureManager::LoadTexture("data files/maps/map02_above_player.png", "Map02_Overlay");
    TextureManager::LoadTexture("data files/maps/map03.png", "Map03");
    TextureManager::LoadTexture("data files/maps/map03_above_player.png", "Map03_Overlay");
    TextureManager::LoadTexture("data files/maps/map04.png", "Map04");
    TextureManager::LoadTexture("data files/maps/map04_above_player.png", "Map04_Overlay");
    TextureManager::LoadTexture("data files/maps/map05.png", "Map05");

    // Sprite
    TextureManager::LoadTexture("data files/graphics/characters/Player.png", "Sprite-Player");
    TextureManager::LoadTexture("data files/graphics/characters/158.png", "Sprite-Guard1");
    TextureManager::LoadTexture("data files/graphics/characters/159.png", "Sprite-Guard2");
    TextureManager::LoadTexture("data files/graphics/characters/17.png", "Sprite-MonsterCow");
    TextureManager::LoadTexture("data files/graphics/characters/BossDragon.png", "Sprite-BossDragon");

    //Equipment
    TextureManager::LoadTexture("data files/graphics/items/2.png", "Equip-AssasinDagger");

    // Item
    TextureManager::LoadTexture("data files/graphics/items/14.png", "Item-HPPotion");

    // Faces
    TextureManager::LoadTexture("data files/graphics/faces/18.png", "Face-Guard1");

    // Skill
    TextureManager::LoadTexture("data files/graphics/animations/13.png", "Skill-Basic Attack");

    session = LOAD_DATA;
}

void Game::loadData()
{
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

    // Load all quest
    QuestDB::LoadQuestDatabase();

    // Load all shop
    ShopDB::LoadShopDatabase();

    // Load all map
    MapManager::LoadMapDatabase();

    loginPanel = new Login();
    registerPanel = new Register();
    session = LOGIN;
}

void Game::loginProcess()
{
    loginPanel->HandleEvent();
    loginPanel->Update();
    loginPanel->Render();
}

void Game::registProcess()
{
    registerPanel->HandleEvent();
    registerPanel->Update();
    registerPanel->Render();
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
        case SDL_QUIT:
            session = SAVE_DATA;
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
                Game::gShop->hideWindow();
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
    // Update Game Object
    currentMap->Update();
    gHUD->Update();
    gHotbar->Update();
    if(!gDialogue->isHide()) gDialogue->Update();
    if(!gInventory->isHide()) gInventory->Update();
    if(!gCharacterInformation->isHide()) gCharacterInformation->Update();
    if(!gShop->isHide()) gShop->Update();

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
    currentMap->RenderBottomLayer();
    gPlayer->Render();
    currentMap->RenderUpperLayer();

    if(!gDialogue->isHide()) gDialogue->Render();
    if(!gInventory->isHide()) gInventory->Render();
    if(!gCharacterInformation->isHide()) gCharacterInformation->Render();
    if(!gShop->isHide()) gShop->Render();
    gHUD->Render();
    gHotbar->Render();

    // Update screen
    SDL_RenderPresent(gRenderer);

    return;
}

void Game::saveData()
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    int l_actor_id = gPlayer->actor_id;
    std::string actor_id = std::to_string(l_actor_id);
    std::string qstr;
    int qstate;

    std::string level = to_string(gPlayer->mStats->Level);
    std::string experience = to_string(gPlayer->mStats->Experience);
    std::string experience_to_next_level = to_string(gPlayer->mStats->ExperienceToNextLevel);
    std::string strength = to_string(gPlayer->mStats->Strength);
    std::string dexterity = to_string(gPlayer->mStats->Dexterity);
    std::string intelligence = to_string(gPlayer->mStats->Intelligence);
    std::string vitality = to_string(gPlayer->mStats->Vitality);
    std::string agility = to_string(gPlayer->mStats->Agility);
    std::string stats_used = to_string(gPlayer->mStats->StatsUsed);
    std::string stats_available = to_string(gPlayer->mStats->StatsAvailable);
    std::string map_id = to_string(currentMap->id);
    std::string x = to_string(static_cast<int>(gPlayer->getTransformComponent()->position.x));
    std::string y = to_string(static_cast<int>(gPlayer->getTransformComponent()->position.y));
    std::string gold = to_string(gInventory->GetGold());
    std::string skin = "Player";

    // Update actor
    qstr = "";
    qstr += "UPDATE `actors` SET `level`='" + level;
    qstr += "',`experience`='" + experience;
    qstr += "',`experience_to_next_level`='" + experience_to_next_level;
    qstr += "',`strength`='" + strength;
    qstr += "',`dexterity`='" + dexterity;
    qstr += "',`intelligence`='" + intelligence;
    qstr += "',`vitality`='" + vitality;
    qstr += "',`agility`='" + agility;
    qstr += "',`stats_used`='" + stats_used;
    qstr += "',`stats_available`='" + stats_available;
    qstr += "',`map_id`='" + map_id;
    qstr += "',`x`='" + x;
    qstr += "',`y`='" + y;
    qstr += "',`gold`='" + gold;
    qstr += "',`skin`='" + skin;
    qstr += "' WHERE `id` = '" + actor_id + "'";

    qstate = mysql_query(conn, qstr.c_str());
    if(qstate)
    {
        std::cout << "Can not make query! (Can not save actor!)" << std::endl;
    }

    // Update inventory
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        std::string slot_id = to_string(i);
        int equipment_id, item_id, item_amount;
        gInventory->FindEquipmentAtSlot(i, &equipment_id);
        gInventory->FindItemAtSlot(i, &item_id, &item_amount);
        qstr = "";
        qstr += "UPDATE `actor_inventory` SET `equipment_id`='" + std::to_string(equipment_id);
        qstr += "',`item_id`='" + std::to_string(item_id);
        qstr += "',`item_amount`='" + std::to_string(item_amount);
        qstr += "' WHERE `slot_id` ='" + slot_id;
        qstr += "' AND `actor_id` ='" + actor_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(qstate)
        {
            std::cout << "Can not make query! (Can not save actor inventory!)" << std::endl;
        }
    }

    // Update player CC's
    for(int i = 0; i < MAX_EQUIPMENT_SLOTS; i++)
    {
        std::string slot_id = to_string(i);
        int equipment_id;
        gCharacterInformation->FindEquipmentAtSlot(i, &equipment_id);
        qstr = "";
        qstr += "UPDATE `actor_character_information` SET `equipment_id`='" + std::to_string(equipment_id);
        qstr += "' WHERE `slot_id` ='" + slot_id;
        qstr += "' AND `actor_id` ='" + actor_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(qstate)
        {
            std::cout << "Can not make query! (Can not save actor CC's!)" << std::endl;
        }
    }

    // Update player variable
    for(auto& v : gQuestLog->mVariable)
    {
        std::string variable_id = std::to_string(v.first);
        std::string variable_value = std::to_string(v.second);
        qstr = "SELECT * FROM `actor_variable` WHERE `actor_id` = '" + actor_id + "' AND `variable_id` = '" + variable_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            // Exist variable
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                qstr = "UPDATE `actor_variable` SET `variable_value` = '" + variable_value;
                qstr += "' WHERE `actor_id` = '" + actor_id + "' AND `variable_id` = '" + variable_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor variable #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_variable(actor_id, variable_id, variable_value) ";
                qstr += "VALUES('" + actor_id + "','" + variable_id + "','" + variable_value + "')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor variable #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor variable #3!)" << std::endl;
        }
    }

    // Update player monster kills
    for(auto& k : gQuestLog->totalMonsterKilled)
    {
        std::string monster_id = std::to_string(k.first);
        std::string amount = std::to_string(k.second);
        qstr = "SELECT * FROM `actor_monster_kills` WHERE `actor_id` = '" + actor_id + "' AND `monster_id` = '" + monster_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                qstr = "UPDATE `actor_monster_kills` SET `amount` = '" + amount;
                qstr += "' WHERE `actor_id` = '" + actor_id + "' AND `monster_id` = '" + monster_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor monster_kills #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_monster_kills(actor_id, monster_id, amount) ";
                qstr += "VALUES('" + actor_id + "','" + monster_id + "','" + amount + "')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor monster_kills #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor monster_kills #3!)" << std::endl;
        }
    }

    // Update player quests
    for(auto& q : gQuestLog->onGoingQuest)
    {
        std::string quest_id = std::to_string(q.first);
        qstr = "SELECT * FROM `actor_quest` WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            // Exist variable
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                if(q.second) qstr = "UPDATE `actor_quest` SET `progress` = '1'";
                else qstr = "UPDATE `actor_quest` SET `progress` = '0'";
                qstr += " WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor on going quest #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_quest(actor_id, quest_id, progress) ";
                if(q.second) qstr += "VALUES('" + actor_id + "','" + quest_id + "','1')";
                else qstr += "VALUES('" + actor_id + "','" + quest_id + "','0')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor on going quest #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor on going quest #3!)" << std::endl;
        }
    }

    for(auto& q : gQuestLog->finishedQuest)
    {
        std::string quest_id = std::to_string(q.first);
        qstr = "SELECT * FROM `actor_quest` WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                qstr = "UPDATE `actor_quest` SET `progress` = '2'";
                qstr += " WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor finished quest #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_variable(actor_id, quest_id, progress) ";
                qstr += "VALUES('" + actor_id + "','" + quest_id + "','2')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor finished quest #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor finished quest #3!)" << std::endl;
        }
    }

    std::cout << "Player data was saved!" << std::endl;
    session = CLEAR;
}

void Game::clean()
{
    TextureManager::CleanTexture();
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    mysql_close(conn);

    gWindow = NULL;
    gRenderer = NULL;
    conn = NULL;

    delete loginPanel;
    delete registerPanel;
    cout << "Game cleaned" << endl;

    return;
}
