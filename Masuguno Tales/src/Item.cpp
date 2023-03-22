#include "Item.h"
#include "TextureManager.h"

Item::Item(int _id, const char* spritePath, int _maxStack, const char* _itemTag, std::string _itemName, std::function<void()> func)
: id(_id), maxStack(_maxStack), itemTag(_itemTag), itemName(_itemName), ItemFunction([this, func] {func();}), currentStack(1)
{
    itemSprite = TextureManager::LoadTexture(spritePath);
}

void Item::Perform()
{
    ItemFunction();
}
Item::~Item()
{
    SDL_DestroyTexture(itemSprite);
    itemSprite = NULL;
}
