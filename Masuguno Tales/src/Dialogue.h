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
            dialogueOption1->handleEvent(&Game::event);
            dialogueOption2->handleEvent(&Game::event);
            dialogueOption3->handleEvent(&Game::event);
            dialogueOption4->handleEvent(&Game::event);
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
            dialogueOption1->Render();
            dialogueOption2->Render();
            dialogueOption3->Render();
            dialogueOption4->Render();
            closeButton->Render();
        }
    }
    void setFace(const char* facePath);
    void setTitleLabel(const char* title);
    void setContentLabel(const char* content);
    void setOption1(const char* text, std::function<void()> func = []{});
    void setOption2(const char* text, std::function<void()> func = []{});
    void setOption3(const char* text, std::function<void()> func = []{});
    void setOption4(const char* text, std::function<void()> func = []{});
private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* DialogueBox;
    SDL_Texture* Face;
    SDL_Rect srcRect, destRect;
    SDL_Rect faceSrcRect, faceDestRect;

    Label* dialogueTitle;
    Label* dialogueContent;
    Label* dialogueOption1;
    Label* dialogueOption2;
    Label* dialogueOption3;
    Label* dialogueOption4;
    Button* closeButton;
};

#endif // Dialogue_h
