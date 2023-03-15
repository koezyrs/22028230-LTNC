#pragma once
#ifndef Inventory_h
#define Inventory_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Game.h"
#include "Window.h"
#include "Component/Component.h"
#include "Button.h"
#include "Label.h"

class Inventory : public Window
{
public:
    Inventory(int _x, int _y, int _width, int _height);

    ~Inventory();
    void Update() override
    {
        if(!isHide())
        {
            closeButton->handleEvent(&Game::event);
        }
    }

    void Render() override
    {
        if(!isHide())
        {
            TextureManager::Draw(InventoryBox, srcRect, destRect);
            inventoryTitle->Render();
            closeButton->Render();
        }
    }
private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* InventoryBox;
    SDL_Rect srcRect, destRect;

    Label* inventoryTitle;
    Button* closeButton;
};

#endif // Inventory_h

