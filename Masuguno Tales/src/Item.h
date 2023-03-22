#pragma once
#ifndef Item_h
#define Item_h

#include <SDL.h>
#include <string>
#include <functional>

class Item
{
public:
    Item(int _id, const char* spritePath, int _maxStack, const char* _itemTag, std::string _itemName, std::function<void()> func = []{});
    ~Item();
    SDL_Texture* getItemSprite() {return itemSprite;}
    void Perform();
    bool isActive() {return active;}
    void destroy() {active = false;}
    int id;
    int maxStack;
    int currentStack;
    const char* itemTag;
    const char* description;
    std::string itemName;
private:
    bool active = true;
    std::function<void()> ItemFunction;

    SDL_Texture* itemSprite;;
};

#endif // Item_h
