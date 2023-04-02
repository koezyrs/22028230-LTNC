#include "Inventory.h"

Inventory::Inventory(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)
{
    InventoryBox = TextureManager::GetTexture("Inventory");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 181, _y + 3, 13, 13, [this]{Window::hideWindow(); });
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

bool Inventory::AddItem(Item* _item)
{
    for(auto& theItem : itemList)
    {
        if(theItem->itemName == _item->itemName && theItem->currentStack < theItem->maxStack)
        {
            delete _item;
            theItem->currentStack = theItem->currentStack + 1;
            return true;
        }
    }

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull == false)
        {
            itemList.emplace_back(_item);
            invSlot[i].AddItemToSlot(_item);
            std::cout << "Added " << _item->itemName << " to the Inventory!" << std::endl;
            return true;
        }
    }
    std::cout << "Inventory full!" << std::endl;
    return false;
}

bool Inventory::AddEquipment(Equipment* _equipment)
{
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull == false)
        {
            equipmentList.emplace_back(_equipment);
            invSlot[i].AddEquipmentToSlot(_equipment);
            std::cout << "Added " << _equipment->equipmentName << " to the Inventory!" << std::endl;
            return true;
            break;
        }
    }

    std::cout << "Inventory full!" << std::endl;
    return false;
}

Inventory::~Inventory()
{
    delete closeButton;
    delete inventoryTitle;
    delete invSlot;

    InventoryBox = NULL;
}

