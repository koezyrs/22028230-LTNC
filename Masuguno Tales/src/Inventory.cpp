#include "Inventory.h"

Inventory::Inventory(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)
{
    InventoryBox = TextureManager::LoadTexture("data files/graphics/gui/Inventory.png");
    closeButton = new Button("data files/graphics/gui/8.png", "data files/graphics/gui/9.png", _x + 181, _y + 3, 13, 13, [this]{Window::hideWindow(); });
    inventoryTitle = new Label("data files/font/game.ttf", "Inventory", 10, _x + 5, _y + 5, SDL_Color{255,255,255}, false, []{});
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};

    int slot = 0;
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            invSlot[slot].init(position.x + 7 + j*39, position.y + 25 + i*39);
            slot++;
        }
    }

}

void Inventory::AddItem(Item* _item)
{
    itemList.emplace_back(_item);
    std::cout << "Added " << _item->itemName << " to the Inventory!" << std::endl;
}

Inventory::~Inventory()
{
    delete closeButton;
    delete inventoryTitle;
    delete invSlot;

    SDL_DestroyTexture(InventoryBox);
    InventoryBox = NULL;
}

