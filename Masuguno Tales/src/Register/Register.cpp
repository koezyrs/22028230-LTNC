#include "Register.h"

Register::Register()
{
    registPanelTexture = TextureManager::GetTexture("Register");
    username_input = new InputBox(450,233, 122, 10, 20);
    password_input = new InputBox(450,266, 122, 10, 20, true);
    retype_password_input = new InputBox(450,302, 122, 10, 20, true);
    email_input = new InputBox(450,334, 122, 10, 20);
    button_regist = new Button("RegistButtonOut","RegistButtonOver",446,355,56,21, [this]{RegistButon();});
    button_back = new Button("BackButtonOut","BackButtonOver",523,356,56,21, [this]{BackButton();});;
    username_input->setActive();
}

Register::~Register()
{
    delete username_input;
    delete password_input;
    delete retype_password_input;
    delete email_input;
    delete button_regist;
    delete button_back;
}

void Register::HandleEvent()
{
    SDL_PollEvent(&Game::event);
    switch(Game::event.type){
        case SDL_QUIT:
            Game::session = CLEAR;
            break;
        case SDL_KEYDOWN:
            if(Game::event.key.keysym.sym == SDLK_RETURN) RegistButon();
            if(Game::event.key.keysym.sym == SDLK_TAB)
                {
                    if(username_input->isActive()) {username_input->deActive(); password_input->setActive();}
                    else if(password_input->isActive()) {password_input->deActive(); retype_password_input->setActive();}
                    else if(retype_password_input->isActive()) {retype_password_input->deActive(); email_input->setActive();}
                    else if(email_input->isActive()) {email_input->deActive(); username_input->setActive();}
                }
            break;
        default:
            break;
        }

    username_input->handleEvent(&Game::event);
    password_input->handleEvent(&Game::event);
    retype_password_input->handleEvent(&Game::event);
    email_input->handleEvent(&Game::event);
    button_regist->handleEvent(&Game::event);
    button_back->handleEvent(&Game::event);
}

void Register::Update()
{

}

void Register::Render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(Game::gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(Game::gRenderer);

    SDL_RenderCopy(Game::gRenderer, registPanelTexture, NULL, NULL);
    username_input->Render();
    password_input->Render();
    retype_password_input->Render();
    email_input->Render();
    button_regist->Render();
    button_back->Render();

     // Update screen
    SDL_RenderPresent(Game::gRenderer);
}

void Register::RegistButon()
{
    /*
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
    */
}

void Register::BackButton()
{
    Game::session = LOGIN;
}
