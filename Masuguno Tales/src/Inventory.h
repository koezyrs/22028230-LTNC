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
#include "Equipment.h"
#include "Settings.h"

struct InventorySlot
{
    InventorySlot() {}
    void init(int _x, int _y)
    {
        SDL_Color White = {255, 255, 255};
        stackLabel = new Label("data files/font/game.ttf", " ", 10, _x + 26, _y + 24, White, 20, false, []{});
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

            if(item != NULL)
            {
                std::string tmp = std::to_string(item->currentStack);
                SDL_Color White = {255, 255, 255};
                stackLabel->Reset();
                stackLabel = new Label("data files/font/game.ttf", tmp.c_str(), 10, destRect.x + 26, destRect.y + 24,  White, 20, false, []{});
            }

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && item != NULL)
            {
                std::cout << "You have use the " << item->itemName << "!" << std::endl;
                item->Perform();
                item->currentStack = item->currentStack - 1;
                if(item->currentStack <= 0)
                {
                    item->destroy();
                    Reset();
                }
            }

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {
                std::cout << "You have equip the " << equipment->equipmentName << "!" << std::endl;
                equipment->destroy();
                Reset();
            }

        }
    }

    void Reset()
    {
        item = NULL;
        equipment = NULL;
        stackLabel->Reset();
        isFull = false;
    }

    void AddItemToSlot(Item* _item)
    {
        Reset();
        item = _item;
        isFull = true;
    }

    void AddEquipmentToSlot(Equipment* _equipment)
    {
        Reset();
        equipment = _equipment;
        isFull = true;
    }

    bool isFull = false;
    Item* item = NULL;
    Equipment* equipment = NULL;
    Label* stackLabel;
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

            equipmentList.erase(std::remove_if(equipmentList.begin(), equipmentList.end(),
                        [](Equipment* theEquipment){return !theEquipment->isActive();}), equipmentList.end());

            closeButton->handleEvent(&Game::event);

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

            for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
            {
                if(invSlot[i].isFull)
                {
                    if(invSlot[i].item != NULL) TextureManager::Draw(invSlot[i].item->getItemSprite(), invSlot[i].srcRect, invSlot[i].destRect);
                    if(invSlot[i].equipment != NULL) TextureManager::Draw(invSlot[i].equipment->getEquipmentSprite(), invSlot[i].srcRect, invSlot[i].destRect);
                    if(invSlot[i].stackLabel != NULL) invSlot[i].stackLabel->Render();
                }
            }

        }
    }

    void AddItem(Item* _item);
    void AddEquipment(Equipment* _equipment);
private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* InventoryBox;
    SDL_Rect srcRect, destRect;

    std::vector<Item*> itemList;
    std::vector<Equipment*> equipmentList;

    InventorySlot* invSlot = new InventorySlot[MAX_INVENTORY_SLOTS];
    Label* inventoryTitle;
    Button* closeButton;
};

#endif // Inventory_h

