#pragma once
#ifndef Dialogue_h
#define Dialogue_h

#include <string>
#include "Window.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Component/Component.h"

class Dialogue : public Window
{
public:
    Dialogue(int _x, int _y, int _width, int _height, std::string title) : Window::Window()
    {
        position.x = _x;
        position.y = _y;

        mWidth = _width;
        mHeight = _height;

        srcRectTitle.x = srcRectTitle.y = srcRectBox.x = srcRectBox.y = 0;
        destRectBox.x = _x;
        destRectBox.y = _y;
        destRectTitle.x = _x + 10;
        destRectTitle.y = _y + 5;
        srcRectBox.w = destRectBox.w = _width;
        srcRectBox.h = destRectBox.h = _height;

        mTitleName = title;
        font = TTF_OpenFont("data files/font/game.ttf", 10);
        DialogueBox = TextureManager::LoadTexture("data files/graphics/gui/Dialogue.png");
        TitleText = TextureManager::LoadText(font, mTitleName.c_str(), SDL_Color{255,255,255});
        SDL_QueryTexture(TitleText, NULL, NULL, &destRectTitle.w, &destRectTitle.h);
    }

    ~Dialogue()
    {
        SDL_DestroyTexture(DialogueBox);
        SDL_DestroyTexture(TitleText);
        TTF_CloseFont(font);

        DialogueBox = NULL;
        TitleText = NULL;
        font = NULL;
    }
    void Update() override
    {

    }

    void Render() override
    {
        if(!isHide())
        {
            TextureManager::Draw(DialogueBox, srcRectBox, destRectBox);
            TextureManager::Draw(TitleText, srcRectTitle, destRectTitle);
        }
    }
private:
    std::string mTitleName;
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* DialogueBox;
    SDL_Texture* TitleText;
    TTF_Font* font;
    SDL_Rect srcRectBox, destRectBox;
    SDL_Rect srcRectTitle, destRectTitle;
};

#endif // Dialogue_h
