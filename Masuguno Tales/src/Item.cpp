#include "Item.h"

Item::Item(int _id, std::string spriteName, int _maxStack, const char* _itemTag, std::string _itemName, std::function<void()> func)
: id(_id), maxStack(_maxStack), currentStack(1), itemTag(_itemTag), description(NULL), itemName(_itemName), ItemFunction([this, func] {func();})
{
    itemSprite = TextureManager::GetTexture(spriteName);
}

SDL_Texture* Item::getItemSprite()
{
    return itemSprite;
}

void Item::Perform()
{
    ItemFunction();
}

bool Item::isActive()
{
    return active;
}

void Item::destroy()
{
    active = false;
}

Item::~Item()
{
    itemSprite = NULL;
}
