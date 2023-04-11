#include "CharacterInformation.h"

struct EquipmentSlot
{
    EquipmentSlot() {}
    void init(int _x, int _y)
    {
        srcRect = {0,0,32,32};
        destRect = {_x, _y,32,32};
        lastClick = 0;
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

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {
                if(SDL_GetTicks64() - 250 <= lastClick)     // Double Click
                {
                    if(AddEquipmentToInventory(equipment))
                    {
                        std::cout << "You have unequip the " << equipment->equipmentName << "!" << std::endl;
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
    }

    void Reset()
    {
        equipment = NULL;
        isFull = false;
    }

    void Equip(Equipment* _equipment)
    {
        Reset();
        equipment = _equipment;
        isFull = true;
    }

    bool AddEquipmentToInventory(Equipment* _equipment)
    {
        if(Game::gInventory->AddEquipment(_equipment))
        {
            Game::gPlayer->mStats->Strength -= _equipment->Strength;
            Game::gPlayer->mStats->Dexterity -= _equipment->Dexterity;
            Game::gPlayer->mStats->Intelligence -= _equipment->Intelligence;
            Game::gPlayer->mStats->Vitality -= _equipment->Vitality;
            Game::gPlayer->mStats->Agility -= _equipment->Agility;
            return true;
        }
        return false;
    }

    bool isFull = false;
    Equipment* equipment = NULL;
    SDL_Rect srcRect, destRect;
    Uint64 lastClick;
};

CharacterInformation::CharacterInformation(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)
{
    CharacterInformationBox = TextureManager::GetTexture("CharacterInformation");
    equipSlot = new EquipmentSlot[MAX_EQUIPMENT_SLOTS];
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 190, _y + 4, 13, 13, [this]{Window::hideWindow(); });
    characterInformationTitle = new Label("data files/font/game.ttf", "Character Information", 10, _x + 5, _y + 5, White, false, []{});

    // Information tab
    std::string playerName = Game::gPlayer->getNameComponent()->mName;
    name = new Label(GAME_FONT, playerName.c_str(), 10, _x + 58, _y + 62, Black, 90, false, []{});
    playerClass = new Label(GAME_FONT, "Adventure", 10, _x + 58, _y + 83, Black, 90, false, []{});
    level = new Label(GAME_FONT, " ", 10, _x + 58, _y + 104, Black, 90, false, []{});
    damage = new Label(GAME_FONT, " ", 10, _x + 68, _y + 127, Black, 90, false, []{});
    defense = new Label(GAME_FONT, " ", 10,_x + 68, _y + 150, Black, 74, false,  []{});
    health = new Label(GAME_FONT, " ", 10,_x + 60, _y + 175, Black, 90, false, []{});
    mana = new Label(GAME_FONT, " ", 10,_x + 60, _y + 198, Black, 90, false, []{});
    attackSpeed = new Label(GAME_FONT, " ", 10,_x + 90, _y + 218, Black, 64, false, []{});

    // Attribute tab
    strength = new Label(GAME_FONT, " ", 10, _x + 38, _y + 261, White, 64, false, []{});
    dexterity = new Label(GAME_FONT, " ", 10, _x + 38, _y + 284, White, 64, false, []{});
    intelligence = new Label(GAME_FONT, " ", 10, _x + 38, _y + 307, White, 64, false, []{});
    vitality = new Label(GAME_FONT, " ", 10, _x + 38, _y + 330, White, 64, false, []{});
    agility = new Label(GAME_FONT, " ", 10, _x + 38, _y + 353, White, 64, false, []{});

    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};

    for(int i = 0; i < 10; i++)
    {
        equipSlot[i].init(position.x + 166, position.y + 27 + i*39);
    }
}

CharacterInformation::~CharacterInformation()
{
    delete characterInformationTitle;
    delete closeButton;

    delete name;
    delete playerClass;
    delete level;
    delete damage;
    delete defense;
    delete health;
    delete mana;
    delete attackSpeed;
    delete strength;
    delete dexterity;
    delete intelligence;
    delete vitality;
    delete agility;
    //delete avaliblePoints;
    //delete pointsText;

    CharacterInformationBox = NULL;
}

void CharacterInformation::Update()
{
    if(isHide()) return;
    equipmentList.erase(std::remove_if(equipmentList.begin(), equipmentList.end(),
               [](Equipment* theEquipment){return !theEquipment->isActive();}), equipmentList.end());

    closeButton->handleEvent(&Game::event);

    for(int i = 0; i < MAX_EQUIPMENT_SLOTS; i++)
    {
        equipSlot[i].handleEvent(&Game::event);
    }

    // Infor Mation tab
    std::string newLevel = to_string(Game::gPlayer->mStats->Level);
    if(LevelStr != newLevel)
    {
        level->Reset();
        LevelStr = newLevel;
        level = new Label(GAME_FONT, LevelStr.c_str(), 10, position.x + 58, position.y + 104, Black, 90, false, []{});
    }

    std::string newDamge = to_string(Game::gPlayer->mStats->Damage);
    if(DamageStr != newDamge)
    {
        damage->Reset();
        DamageStr = newDamge;
        damage = new Label(GAME_FONT, DamageStr.c_str(), 10, position.x + 68, position.y + 127, Black, 90, false, []{});
    }

    std::string newDefense = to_string(Game::gPlayer->mStats->Defense);
    if(DefenseStr != newDefense)
    {
        defense->Reset();
        DefenseStr = newDefense;
        defense = new Label(GAME_FONT, DefenseStr.c_str(), 10, position.x + 68, position.y + 150, Black, 74, false,  []{});
    }

    std::string newHP = to_string(Game::gPlayer->mStats->Health) + "/" + to_string(Game::gPlayer->mStats->MaxHealth);
    if(HPStr != newHP)
    {
        health->Reset();
        HPStr = newHP;
        health = new Label(GAME_FONT, HPStr.c_str(), 10, position.x + 60, position.y + 175, Black, 90, false, []{});
    }

    std::string newMP = to_string(Game::gPlayer->mStats->Mana) + "/" + to_string(Game::gPlayer->mStats->MaxMana);
    if(MPStr != newMP)
    {
        mana->Reset();
        MPStr = newMP;
        mana = new Label(GAME_FONT, MPStr.c_str(), 10, position.x + 60, position.y + 198, Black, 90, false, []{});
    }

    std::string newAS = to_string(Game::gPlayer->mStats->AttackSpeed);
    if(ASStr != newAS)
    {
        attackSpeed->Reset();
        ASStr = newAS;
        attackSpeed = new Label(GAME_FONT, ASStr.c_str(), 10, position.x + 90, position.y + 218, Black, 64, false, []{});
    }

    // Attribute tab
    std::string newStrength = to_string(Game::gPlayer->mStats->Strength);
    if(strengthStr != newStrength)
    {
        strength->Reset();
        strengthStr = newStrength;
        strength = new Label(GAME_FONT, strengthStr.c_str(), 10, position.x + 38, position.y + 261, White, 64, false, []{});
    }

    std::string newDex = to_string(Game::gPlayer->mStats->Dexterity);
    if(dexterityStr != newDex)
    {
        dexterity->Reset();
        dexterityStr = newDex;
        dexterity = new Label(GAME_FONT, dexterityStr.c_str(), 10, position.x + 38, position.y + 284, White, 64, false, []{});

    }

    std::string newIntell = to_string(Game::gPlayer->mStats->Intelligence);
    if(intelligenceStr != newIntell)
    {
        intelligence->Reset();
        intelligenceStr = newIntell;
        intelligence = new Label(GAME_FONT, intelligenceStr.c_str(), 10, position.x + 38, position.y + 307, White, 64, false, []{});
    }

    std::string newVital = to_string(Game::gPlayer->mStats->Vitality);
    if(vitalityStr != newVital)
    {
        vitality->Reset();
        vitalityStr = newVital;
        vitality = new Label(GAME_FONT, vitalityStr.c_str(), 10, position.x + 38, position.y + 330, White, 64, false, []{});
    }

    std::string newAgi = to_string(Game::gPlayer->mStats->Agility);
    if(agilityStr != newAgi)
    {
        agility->Reset();
        agilityStr = newAgi;
        agility = new Label(GAME_FONT, agilityStr.c_str(), 10, position.x + 38, position.y + 353, White, 64, false, []{});
    }

}

void CharacterInformation::Render()
{
    if(isHide()) return;
    TextureManager::Draw(CharacterInformationBox, srcRect, destRect);
    characterInformationTitle->Render();
    closeButton->Render();

    for(int i = 0; i < MAX_EQUIPMENT_SLOTS; i++)
    {
        if(equipSlot[i].isFull)
        {
            TextureManager::Draw(equipSlot[i].equipment->getEquipmentSprite(), equipSlot[i].srcRect, equipSlot[i].destRect);
        }
    }

    name->Render();
    playerClass->Render();
    level->Render();
    damage->Render();
    defense->Render();
    health->Render();
    mana->Render();
    attackSpeed->Render();

    strength->Render();
    dexterity->Render();
    intelligence->Render();
    vitality->Render();
    agility->Render();
}

bool CharacterInformation::AddEquipment(Equipment* _equipment)
{
    EQUIPMENT_TAG equipmentTag = _equipment->equipmentTag;
    switch(equipmentTag)
    {
    case WEAPON:
        if(equipSlot[0].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip weapon!" << std::endl;
            return false;
        }
        equipSlot[0].Equip(_equipment);
        return true;
        break;
    case SHIELD:
        if(equipSlot[1].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip shield!" << std::endl;
            return false;
        }
        equipSlot[1].Equip(_equipment);
        return true;
        break;
    case HELMET:
        if(equipSlot[2].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip helmet!" << std::endl;
            return false;
        }
        equipSlot[2].Equip(_equipment);
        return true;
        break;
    case ARMOR:
        if(equipSlot[3].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip armor!" << std::endl;
            return false;
        }
        equipSlot[3].Equip(_equipment);
        return true;
        break;
    case GLOVE:
        if(equipSlot[4].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip glove!" << std::endl;
            return false;
        }
        equipSlot[4].Equip(_equipment);
        return true;
        break;
    case SHOES:
        if(equipSlot[5].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip shoes!" << std::endl;
            return false;
        }
        equipSlot[5].Equip(_equipment);
        return true;
        break;
    case CAPE:
        if(equipSlot[6].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip cape!" << std::endl;
            return false;
        }
        equipSlot[6].Equip(_equipment);
        return true;
        break;
    case RING:
        if(equipSlot[7].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip ring!" << std::endl;
            return false;
        }
        equipSlot[7].Equip(_equipment);
        return true;
        break;
    case NECKLACE:
        if(equipSlot[8].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip necklace!" << std::endl;
            return false;
        }
        equipSlot[8].Equip(_equipment);
        return true;
        break;
    case MEDAL:
        if(equipSlot[9].isFull)
        {
            equipmentList.emplace_back(_equipment);
            std::cout << "Already equip medal!" << std::endl;
            return false;
        }
        equipSlot[9].Equip(_equipment);
        return true;
        break;
    default:
        break;
    }
    return false;
}

