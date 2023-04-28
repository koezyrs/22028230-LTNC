#include "Shop.h"

struct ShopSlot
{
    ShopSlot() {}
    void init(int _x, int _y)
    {
        SDL_Color White = {255, 255, 255};
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

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && item != NULL)
            {

            }

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {

            }

        }
    }

    void Reset()
    {
        item = NULL;
        equipment = NULL;
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
    SDL_Rect srcRect, destRect;
};

Shop::Shop(int _x, int _y, int _width, int _height, std::string shop_title)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height), gold(0)
{
    ShopBox = TextureManager::GetTexture("Shop");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 257, _y + 5, 13, 13, [this]{Window::hideWindow(); });
    shopTitle = new Label(GAME_FONT, shop_title.c_str(), 10, _x + 5, _y + 5, White, 250);
    goldLabel = new Label(GAME_FONT, " ", 10, _x + 35, _y + 270, White, 250);
    shopSlot = new ShopSlot[MAX_SHOP_SLOTS];
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};

    int slot = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            shopSlot[slot].init(position.x + 8 + j*39, position.y + 27 + i*39);
            slot++;
        }
    }

}

void Shop::Update()
{
    if(isHide()) return;
    itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
                [](Item* theItem){return !theItem->isActive();}), itemList.end());

    equipmentList.erase(std::remove_if(equipmentList.begin(), equipmentList.end(),
                [](Equipment* theEquipment){return !theEquipment->isActive();}), equipmentList.end());

    closeButton->handleEvent(&Game::event);

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        shopSlot[i].handleEvent(&Game::event);
    }

    std::string newGold = std::to_string(gold);
    if(goldStr != newGold)
    {
        goldStr = newGold;
        goldLabel->Reset();
        goldLabel = new Label(GAME_FONT, goldStr.c_str(), 10, position.x + 35, position.y + 270, White, 250);
    }

}

void Shop::Render()
{
    if(isHide()) return;

    TextureManager::Draw(ShopBox, srcRect, destRect);
    shopTitle->Render();
    goldLabel->Render();
    closeButton->Render();

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull)
        {
            if(shopSlot[i].item != NULL) TextureManager::Draw(shopSlot[i].item->getItemSprite(), shopSlot[i].srcRect, shopSlot[i].destRect);
            if(shopSlot[i].equipment != NULL) TextureManager::Draw(shopSlot[i].equipment->getEquipmentSprite(), shopSlot[i].srcRect, shopSlot[i].destRect);
        }
    }
}

bool Shop::AddItem(int item_id)
{
    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return false;
    }

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull == false)
        {
            itemList.emplace_back(new Item(itemTemp.item_id, itemTemp.spriteName,itemTemp.maxStack,itemTemp.itemTag,itemTemp.itemName,itemTemp.ItemFunc));
            shopSlot[i].AddItemToSlot(itemList.back());
            std::cout << "Added " << itemTemp.itemName << " to the Shop!" << std::endl;
            return true;
        }
    }
    std::cout << "Shop full!" << std::endl;
    return false;
}

bool Shop::AddEquipment(int equipment_id)
{
    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull == false)
        {
            equipmentList.emplace_back(new Equipment(equipTemp.equipment_id, equipTemp.spriteName, equipTemp.equipmentTag, equipTemp.equipmentName,
                                                     equipTemp.Strength, equipTemp.Dexterity, equipTemp.Intelligence,
                                                     equipTemp.Vitality, equipTemp.Agility));
            shopSlot[i].AddEquipmentToSlot(equipmentList.back());
            std::cout << "Added " << equipTemp.equipmentName << " to the Shop!" << std::endl;
            return true;
            break;
        }
    }

    std::cout << "Shop full!" << std::endl;
    return false;
}

void Shop::Reset()
{
    itemList.clear();
    equipmentList.clear();
    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        shopSlot[i].Reset();
    }
}

Shop::~Shop()
{
    delete closeButton;
    delete ShopBox;
    delete[] shopSlot;
    delete goldLabel;

    ShopBox = NULL;
}

bool Shop::OpenShop(int shop_id)
{
    if(ShopDB::shopDatabase.count(shop_id) <= 0)
    {
        std::cerr << "Not found shop id: " << shop_id << std::endl;
        return false;
    }
    Reset();
    ShopType shopTemp = ShopDB::shopDatabase[shop_id];
    int item_amount = shopTemp.itemList.size();
    for(auto& i : shopTemp.itemList) AddItem(i);
    int equip_amount = shopTemp.equipmentList.size();
    for(auto& e : shopTemp.equipmentList) AddEquipment(e);
    shopTitle->Reset();
    shopTitle = new Label(GAME_FONT, shopTemp.shop_title.c_str(), 10, position.x + 5, position.y + 5, White, 250);
    showWindow();
    Game::gDialogue->hideWindow();
    return true;
}
