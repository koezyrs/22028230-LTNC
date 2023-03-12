#pragma once
#ifndef Dialogue_h
#define Dialogue_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Window.h"
#include "Game.h"
#include "Component/Component.h"
#include "Button.h"
#include "Label.h"

class Dialogue : public Window
{
public:
    Dialogue(int _x, int _y, int _width, int _height, const char* title);

    ~Dialogue();
    void Update() override
    {
        closeButton->handleEvent(&Game::event);
    }

    void Render() override
    {
        if(!isHide())
        {
            TextureManager::Draw(DialogueBox, srcRect, destRect);
            dialogueTitle->Render();
            closeButton->Render();
        }
    }

private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* DialogueBox;
    SDL_Rect srcRect, destRect;

    Label* dialogueTitle;
    Button* closeButton;
};

#endif // Dialogue_h
