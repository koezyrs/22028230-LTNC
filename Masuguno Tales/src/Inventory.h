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
#include "Button.h"
#include "Label.h"
#include "Item.h"
#include "Equipment.h"
#include "CharacterInformation.h"

#include "Settings.h"
#include "TextureManager.h"

struct InventorySlot;

class Inventory : public Window
{
public:
    Inventory(int _x, int _y, int _width, int _height);

    ~Inventory();
    void Update() override;
    void Render() override;

    bool AddItem(Item* _item);
    bool AddEquipment(Equipment* _equipment);
private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* InventoryBox;
    SDL_Rect srcRect, destRect;

    std::vector<Item*> itemList;
    std::vector<Equipment*> equipmentList;

    InventorySlot* invSlot;
    Label* inventoryTitle;
    Button* closeButton;
};

#endif // Inventory_h

