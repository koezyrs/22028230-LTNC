#include "Item.h"
#include "TextureManager.h"

Item::Item(int _id, std::string spriteName, int _maxStack, const char* _itemTag, std::string _itemName, std::function<void()> func)
: id(_id), maxStack(_maxStack), currentStack(1), itemTag(_itemTag), description(NULL), itemName(_itemName), ItemFunction([this, func] {func();})
{
    itemSprite = TextureManager::GetTexture(spriteName);
}

void Item::Perform()
{
    ItemFunction();
}
Item::~Item()
{
    itemSprite = NULL;
}
