#pragma once
#ifndef Item_h
#define Item_h

#include <SDL.h>
#include <string>
#include <functional>
#include "TextureManager.h"

class Item
{
public:
    Item(int _item_id, std::string spriteName, int _maxStack, const char* _itemTag, std::string _itemName, int _buyPrice, int _sellPrice ,std::function<void()> func = []{});
    ~Item();
    SDL_Texture* getItemSprite();
    void Perform();
    bool isActive();
    void destroy();
    int item_id;
    int maxStack;
    int currentStack;
    const char* itemTag;
    const char* description;
    std::string itemName;
    int buyPrice, sellPrice;
private:
    bool active = true;
    std::function<void()> ItemFunction;

    SDL_Texture* itemSprite;
};

#endif // Item_h
