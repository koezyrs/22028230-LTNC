#pragma once
#ifndef Login_h
#define Login_h

#include <string>

#include "../Game.h"
#include "../InputBox.h"
#include "../Button.h"
#include "../TextureManager.h"

class Login
{
public:
    Login();
    ~Login();
    void HandleEvent();
    void Update();
    void Render();
private:
    void LoginButon();
    void ExitButton();
    void LoadGameDatabase(int account_id);
    SDL_Texture* loginPanelTexture;
    InputBox* username_input;
    InputBox* password_input;
    Button* button_login;
    Button* button_exit;
};

#endif // Login_h
