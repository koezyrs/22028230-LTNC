#include "Login.h"

#include "../Map.h"
#include "../Actor.h"
#include "../Dialogue.h"
#include "../Inventory.h"
#include "../CharacterInformation.h"
#include "../HUD.h"
#include "../Hotbar.h"
#include "../QuestLog.h"

Login::Login()
{
    loginPanelTexture = TextureManager::GetTexture("Login");
    username_input = new InputBox(450,268, 122, 10, 20);
    password_input = new InputBox(450,300, 122, 10, 32, true);
    button_login = new Button("LoginButtonOut","LoginButtonOver",446,319,56,21, [this]{LoginButon();});
    button_exit = new Button("ExitButtonOut","ExitButtonOver",523,319,56,21,[this]{ExitButton();});
    username_input->setActive();
}

Login::~Login()
{
    delete username_input;
    delete password_input;
    delete button_login;
    delete button_exit;
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

void Login::LoadGameDatabase(int account_id)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    std::string qstr = "SELECT * FROM actors WHERE account_id = '" + std::to_string(account_id) + "'";
    int qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        res = mysql_store_result(Game::conn);
        row = mysql_fetch_row(res);
        std::string playerName(row[2]);
        std::string playerSkin(row[17]);
        Game::currentMap = new Map(std::stoi(row[13]));
        Game::gPlayer = new Actor(playerName, std::stoi(row[3]), std::stoi(row[4]), std::stoi(row[5]), std::stoi(row[6]),
                                  std::stoi(row[7]), std::stoi(row[8]), std::stoi(row[9]), std::stoi(row[10]),
                                  std::stoi(row[11]), std::stoi(row[12]), std::stoi(row[14]), std::stoi(row[15]),
                                  playerSkin);
        // Initialize GUI
        Game::gDialogue = new Dialogue((SCREEN_WIDTH - 478)/2 , (SCREEN_HEIGHT - 226)/2, 478, 226, " ", "EmptyFace", " ");
        Game::gInventory = new Inventory(790, 130, 198, 314);
        Game::gCharacterInformation = new CharacterInformation(50,110, 206, 418);
        Game::gHUD = new HUD();
        Game::gHotbar = new Hotbar();
        Game::gQuestLog = new QuestLog();
        Game::session = LOAD_DATA;
    }else
    {
        std::cout << "Khong the thuc hien truy van toi database!" << std::endl;
    }
}
