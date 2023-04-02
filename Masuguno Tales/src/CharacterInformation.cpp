#include "CharacterInformation.h"

CharacterInformation::CharacterInformation(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)
{
    CharacterInformationBox = TextureManager::GetTexture("CharacterInformation");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 190, _y + 4, 13, 13, [this]{Window::hideWindow(); });
    characterInformationTitle = new Label("data files/font/game.ttf", "Character Information", 10, _x + 5, _y + 5, SDL_Color{255,255,255}, false, []{});
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
    /*
    delete information;
    delete name;
    delete playerClass;
    delete level;
    delete guild;
    delete health;
    delete mana;
    delete exp;
    delete premium;
    delete attribute;
    delete strength;
    delete dexterity;
    delete intelligence;
    delete vitality;
    delete agility;
    delete avaliblePoints;
    delete pointsText;
    */
    CharacterInformationBox = NULL;
}
