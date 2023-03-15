#pragma once
#ifndef Inventory_h
#define Inventory_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <algorithm>

#include "Game.h"
#include "Window.h"
#include "Component/Component.h"
#include "Button.h"
#include "Label.h"
#include "Item.h"
#include "Settings.h"

struct InventorySlot
{
    InventorySlot() {}
    void init(int _x, int _y)
    {
        srcRect = {0,0,32,32};
        destRect = {_x, _y,32,32};
    }

    void handleEvent(SDL_Event* e)
    {
        if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            bool inside = false;
            // check if the mouse is in the button
            if((x < destRect.x) || (x > destRect.x + 32) || (y < destRect.y) || (y > destRect.y + 32)) inside = false;
            else inside = true;

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true)
            {
                std::cout << "You have equip the " << item->itemName << "!" << std::endl;
                item->Perform();
                item->destroy();
            }
        }
    }
    void Reset()
    {
        item = NULL;
        isFull = false;
    }
    void AddItemToSlot(Item* _item)
    {
        Reset();
        item = _item;
        isFull = true;
    }
    bool isFull = false;
    Item* item;
    SDL_Rect srcRect, destRect;
};


class Inventory : public Window
{
public:
    Inventory(int _x, int _y, int _width, int _height);

    ~Inventory();
    void Update() override
    {
        if(!isHide())
        {
            itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
                        [](Item* theItem){return !theItem->isActive();}), itemList.end());

            closeButton->handleEvent(&Game::event);
            for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
            {
                invSlot[i].Reset();
            }

            int id = 0;
            for(auto& i :itemList)
            {
                invSlot[id].AddItemToSlot(i);
                id++;
            }

            for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
            {
                invSlot[i].handleEvent(&Game::event);
            }

        }
    }

    void Render() override
    {
        if(!isHide())
        {
            TextureManager::Draw(InventoryBox, srcRect, destRect);
            inventoryTitle->Render();
            closeButton->Render();

            int id = 0;
            for(auto& i : itemList)
            {
                TextureManager::Draw(i->getItemSprite(), invSlot[id].srcRect, invSlot[id].destRect);
                id++;
            }
        }
    }

    void AddItem(Item* _item);
private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* InventoryBox;
    SDL_Rect srcRect, destRect;

    std::vector<Item*> itemList;

    InventorySlot* invSlot = new InventorySlot[MAX_INVENTORY_SLOTS];
    Label* inventoryTitle;
    Button* closeButton;
};

#endif // Inventory_h

