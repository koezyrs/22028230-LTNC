#include "CharacterInformation.h"
#include "Settings.h"

CharacterInformation::CharacterInformation(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)
{
    CharacterInformationBox = TextureManager::GetTexture("CharacterInformation");
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
