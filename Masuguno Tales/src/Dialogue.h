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
    Dialogue(int _x, int _y, int _width, int _height, const char* title, const char* facefile, const char* content);

    ~Dialogue();
    void Update() override
    {
        if(!isHide())
        {
            closeButton->handleEvent(&Game::event);
            dialogueContent->handleEvent(&Game::event);
        }
    }

    void Render() override
    {
        if(!isHide())
        {
            TextureManager::Draw(DialogueBox, srcRect, destRect);
            TextureManager::Draw(Face, faceSrcRect, faceDestRect);
            dialogueTitle->Render();
            dialogueContent->Render();
            closeButton->Render();
        }
    }

private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* DialogueBox;
    SDL_Texture* Face;
    SDL_Rect srcRect, destRect;
    SDL_Rect faceSrcRect, faceDestRect;

    Label* dialogueTitle;
    Label* dialogueContent;
    Button* closeButton;
};

#endif // Dialogue_h
