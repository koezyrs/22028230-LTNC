#include "Inventory.h"

struct InventorySlot
{
    InventorySlot() {}
    void init(int _x, int _y)
    {
        SDL_Color White = {255, 255, 255};
        stackLabel = new Label("data files/font/game.ttf", " ", 10, _x + 26, _y + 24, White, 20, false, []{});
        srcRect = {0,0,32,32};
        destRect = {_x, _y,32,32};
        lastClick = 0;
        lastUpdateStack = 0;
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

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && item != NULL)
            {
                if(SDL_GetTicks64() - 250 <= lastClick)     // Double Click
                {
                    std::cout << "You have use the " << item->itemName << "!" << std::endl;
                    item->Perform();
                    item->currentStack = item->currentStack - 1;
                    if(item->currentStack <= 0)
                    {
                        item->destroy();
                        Reset();
                    }
                }else                                       // Single Click
                {
                    // Show info
                }
                lastClick = SDL_GetTicks64();
            }

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {
                if(SDL_GetTicks64() - 250 <= lastClick)     // Double Click
                {
                    if(AddEquipmentToCharacterInformation(equipment->equipment_id))
                    {
                        std::cerr << "You have equip the " << equipment->equipmentName << "!" << std::endl;
                        equipment->destroy();
                        Reset();
                    }
                }else                                       // Single Click
                {
                    // Show info
                }
                lastClick = SDL_GetTicks64();
            }

        }

        if(item != NULL)
        {
            if(lastUpdateStack != item->currentStack)
            {
                std::string tmp = std::to_string(item->currentStack);
                SDL_Color White = {255, 255, 255};
                lastUpdateStack = item->currentStack;
                stackLabel->Reset();
                stackLabel = new Label("data files/font/game.ttf", tmp.c_str(), 10, destRect.x + 26, destRect.y + 24,  White, 20, false, []{});
            }
        }
    }

    void Reset()
    {
        item = NULL;
        equipment = NULL;
        lastUpdateStack = 0;
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

    bool AddEquipmentToCharacterInformation(int equipment_id)
    {
        EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
        if(equipTemp.equipmentName.empty())
        {
            std::cerr << "Can not find equipment id: " << equipment_id << std::endl;
            return false;
        }

        if(Game::gCharacterInformation->AddEquipment(equipment_id))
        {
            Game::gPlayer->mStats->Strength += equipTemp.Strength;
            Game::gPlayer->mStats->Dexterity += equipTemp.Dexterity;
            Game::gPlayer->mStats->Intelligence += equipTemp.Intelligence;
            Game::gPlayer->mStats->Vitality += equipTemp.Vitality;
            Game::gPlayer->mStats->Agility += equipTemp.Agility;
            return true;
        }
        return false;
    }

    bool isFull = false;
    Item* item = NULL;
    Equipment* equipment = NULL;
    Label* stackLabel;
    int lastUpdateStack;
    SDL_Rect srcRect, destRect;
    Uint64 lastClick;
};

Inventory::Inventory(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)
{
    InventoryBox = TextureManager::GetTexture("Inventory");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 181, _y + 3, 13, 13, [this]{Window::hideWindow(); });
    inventoryTitle = new Label(GAME_FONT, "Inventory", 10, _x + 5, _y + 5, SDL_Color{255,255,255}, false, []{});
    invSlot = new InventorySlot[MAX_INVENTORY_SLOTS];
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

void Inventory::Update()
{
    if(isHide()) return;
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

void Inventory::Render()
{
    if(isHide()) return;

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

bool Inventory::AddItem(int item_id)
{
    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return false;
    }
    for(auto& theItem : itemList)
    {
        if(theItem->itemName == itemTemp.itemName && theItem->currentStack < theItem->maxStack)
        {
            theItem->currentStack = theItem->currentStack + 1;
            return true;
        }
    }

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull == false)
        {
            itemList.emplace_back(new Item(itemTemp.item_id, itemTemp.spriteName,itemTemp.maxStack,itemTemp.itemTag,itemTemp.itemName,itemTemp.ItemFunc));
            invSlot[i].AddItemToSlot(itemList.back());
            std::cout << "Added " << itemTemp.itemName << " to the Inventory!" << std::endl;
            return true;
        }
    }
    std::cout << "Inventory full!" << std::endl;
    return false;
}

bool Inventory::AddEquipment(int equipment_id)
{
    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull == false)
        {
            equipmentList.emplace_back(new Equipment(equipTemp.equipment_id, equipTemp.spriteName, equipTemp.equipmentTag, equipTemp.equipmentName,
                                                     equipTemp.Strength, equipTemp.Dexterity, equipTemp.Intelligence,
                                                     equipTemp.Vitality, equipTemp.Agility));
            invSlot[i].AddEquipmentToSlot(equipmentList.back());
            std::cout << "Added " << equipTemp.equipmentName << " to the Inventory!" << std::endl;
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

bool Inventory::FindItem(int item_id, int item_amount)
{
    int amount = 0;
    bool success = false;

    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return false;
    }

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(amount >= item_amount) {success = true; break;}
        if(!invSlot[i].isFull) continue;
        if(invSlot[i].item == NULL) continue;
        if(invSlot[i].item->item_id == itemTemp.item_id) amount = amount + invSlot[i].item->currentStack;
    }

    return success;
}

bool Inventory::FindEquip(int equip_id, int equip_amount)
{
    int amount = 0;
    bool success = false;

    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equip_id];

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(amount >= equip_amount) {success = true; break;}
        if(!invSlot[i].isFull) continue;
        if(invSlot[i].equipment == NULL) continue;
        if(invSlot[i].equipment->equipment_id == equipTemp.equipment_id) amount = amount + 1;
    }
    return success;
}

void Inventory::AddEquipmentToSlot(int slot_id, int equipment_id)
{
    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
    if(equipTemp.equipmentName.empty())
    {
        std::cerr << "Not found equip id: " << equipment_id << std::endl;
        return;
    }
    equipmentList.emplace_back(new Equipment(equipTemp.equipment_id, equipTemp.spriteName, equipTemp.equipmentTag, equipTemp.equipmentName,
                                            equipTemp.Strength, equipTemp.Dexterity, equipTemp.Intelligence,
                                            equipTemp.Vitality, equipTemp.Agility));
    invSlot[slot_id].AddEquipmentToSlot(equipmentList.back());
    std::cout << "Added " << equipTemp.equipmentName << " to the Inventory!" << std::endl;
}

void Inventory::AddItemToSlot(int slot_id, int item_id, int item_amount)
{
    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return;
    }

    itemList.emplace_back(new Item(itemTemp.item_id, itemTemp.spriteName,itemTemp.maxStack,itemTemp.itemTag,itemTemp.itemName,itemTemp.ItemFunc));
    itemList.back()->currentStack = itemList.back()->currentStack + item_amount - 1;
    invSlot[slot_id].AddItemToSlot(itemList.back());
    std::cout << "Added " << itemTemp.itemName << " to the Inventory!" << std::endl;
}
