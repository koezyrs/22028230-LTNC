#include "Login.h"


Login::Login()
{
    loginPanelTexture = TextureManager::GetTexture("Login");
    username_input = new InputBox(450,268, 122, 10, 20);
    password_input = new InputBox(450,300, 122, 10, 32, true);
    button_login = new Button("LoginButtonOut","LoginButtonOver",446,319,56,21, [this]{LoginButon();});
    button_exit = new Button("ExitButtonOut","ExitButtonOver",523,319,56,21,[this]{ExitButton();});
    button_register = new Button("RegistButtonOut","RegistButtonOver",558,345,56,21,[this]{RegistButton();});
    username_input->setActive();
}

Login::~Login()
{
    delete username_input;
    delete password_input;
    delete button_login;
    delete button_exit;
    delete button_register;
}

void Login::HandleEvent()
{
    SDL_PollEvent(&Game::event);
    switch(Game::event.type){
        case SDL_QUIT:
            Game::session = CLEAR;
            break;
        case SDL_KEYDOWN:
            if(Game::event.key.keysym.sym == SDLK_RETURN) LoginButon();
            if(Game::event.key.keysym.sym == SDLK_TAB) {username_input->toogle(); password_input->toogle();}
            break;
        default:
            break;
        }

    username_input->handleEvent(&Game::event);
    password_input->handleEvent(&Game::event);
    button_login->handleEvent(&Game::event);
    button_exit->handleEvent(&Game::event);
    button_register->handleEvent(&Game::event);
}

void Login::Update()
{

}

void Login::Render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(Game::gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(Game::gRenderer);

    SDL_RenderCopy(Game::gRenderer, loginPanelTexture, NULL, NULL);
    username_input->Render();
    password_input->Render();
    button_login->Render();
    button_exit->Render();
    button_register->Render();

     // Update screen
    SDL_RenderPresent(Game::gRenderer);
}

void Login::LoginButon()
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    std::string qstr = "SELECT id FROM accounts WHERE username = '" + username_input->inputValue + "' AND password = '" + password_input->inputValue + "'";
    int qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        res = mysql_store_result(Game::conn);
        row = mysql_fetch_row(res);
        if(row)
        {
            std::cout << "Id cua ban la: " << row[0] << std::endl;
            std::cout << "Dang nhap thanh cong!" << std::endl;
            LoadGameDatabase(std::stoi(row[0]));
        }else
        {
            std::cout << "Sai thong tin dang nhap!" << std::endl;
        }

    }else
    {
        std::cout << "Khong the thuc hien truy van toi database!" << std::endl;
    }
}

void Login::ExitButton()
{
    Game::session = CLEAR;
}

void Login::RegistButton()
{
    Game::session = REGISTER;
}

void Login::LoadGameDatabase(int account_id)
{
    MYSQL_ROW row;
    MYSQL_RES* res;

    std::string actor_id;
    std::string qstr;
    int qstate;

    // Create character
    qstr = "SELECT * FROM actors WHERE account_id = '" + std::to_string(account_id) + "'";
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        res = mysql_store_result(Game::conn);
        row = mysql_fetch_row(res);
        if(!row)
        {
            std::cerr << "Character has not been created!" << std::endl;
            return;
        }
        std::string _actor_id(row[1]);
        actor_id = _actor_id;
        std::string playerName(row[2]);
        std::string playerSkin(row[17]);
        int map_id = std::stoi(row[13]);
        Game::currentMap = new Map(map_id);
        Game::gPlayer = new Actor(playerName, std::stoi(row[3]), std::stoi(row[4]), std::stoi(row[5]), std::stoi(row[6]),
                                  std::stoi(row[7]), std::stoi(row[8]), std::stoi(row[9]), std::stoi(row[10]),
                                  std::stoi(row[11]), std::stoi(row[12]), std::stoi(row[14]), std::stoi(row[15]),
                                  playerSkin);
        MapManager::LoadMap(map_id);
    }else
    {
        std::cout << "Can not make query! (Can not load actor!)" << std::endl;
        return;
    }

    //Inventory
    qstr = "SELECT * FROM actor_inventory WHERE actor_id = '" + actor_id + "' ORDER BY slot_id ASC LIMIT 35"; // 35 == MAX_INVENTORY_SLOTS
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        Game::gInventory = new Inventory(790, 130, 198, 314);
        res = mysql_store_result(Game::conn);
        while(row = mysql_fetch_row(res))
        {
            int equipment_id = stoi(row[3]);
            int item_id = stoi(row[4]);
            int item_amount = stoi(row[5]);
            if(equipment_id > 0) Game::gInventory->AddEquipment(equipment_id);
            else if(item_id > 0)
            {
                for(int i = 1; i <= item_amount; i++) Game::gInventory->AddItem(item_id);
            }
        }

    }else{
        std::cout << "Can not make query! (Can not load inventory!)" << std::endl;
        return;
    }

    // Character Information
    qstr = "SELECT * FROM actor_character_information WHERE actor_id = '" + actor_id + "' ORDER BY slot_id ASC LIMIT 10"; // 10 == MAX_EQUIPMENT_SLOTS
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        Game::gCharacterInformation = new CharacterInformation(50,110, 206, 418);
        res = mysql_store_result(Game::conn);
        while(row = mysql_fetch_row(res))
        {
            int equipment_id = stoi(row[3]);
            if(equipment_id > 0) Game::gCharacterInformation->AddEquipment(equipment_id);
        }
    }else{
        std::cout << "Can not make query! (Can not load character information!)" << std::endl;
        return;
    }

    // Initialize GUI
        Game::gDialogue = new Dialogue((SCREEN_WIDTH - 478)/2 , (SCREEN_HEIGHT - 226)/2, 478, 226, " ", "EmptyFace", " ");
        Game::gHUD = new HUD();
        Game::gHotbar = new Hotbar();
        Game::gQuestLog = new QuestLog();

        Game::session = RUNNING;
}
