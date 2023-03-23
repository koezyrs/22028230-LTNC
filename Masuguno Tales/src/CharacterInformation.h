#pragma once
#ifndef CharacterInformation_h
#define CharacterInformation_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <algorithm>

#include "Game.h"
#include "Window.h"
#include "Component/Component.h"
#include "Button.h"
#include "Label.h"
#include "Equipment.h"
#include "Settings.h"
#include "EventManager.h"

struct EquipmentSlot
{
    EquipmentSlot() {}
    void init(int _x, int _y)
    {
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

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {
                std::cout << "You have unequip the " << equipment->equipmentName << "!" << std::endl;
                EventManager::AddEquipmentToInventory(equipment);
                equipment->destroy();
                Reset();
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

    bool isFull = false;
    Equipment* equipment = NULL;
    SDL_Rect srcRect, destRect;
};


class CharacterInformation : public Window
{
public:
    CharacterInformation(int _x, int _y, int _width, int _height);

    ~CharacterInformation();
    void Update() override
    {
        if(!isHide())
        {
            equipmentList.erase(std::remove_if(equipmentList.begin(), equipmentList.end(),
                       [](Equipment* theEquipment){return !theEquipment->isActive();}), equipmentList.end());

            closeButton->handleEvent(&Game::event);

            for(int i = 0; i < MAX_EQUIPMENT_SLOTS; i++)
            {
                equipSlot[i].handleEvent(&Game::event);
            }

        }
    }

    void Render() override
    {
        if(!isHide())
        {
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

        }
    }

    bool AddEquipment(Equipment* _equipment);
private:
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* CharacterInformationBox;
    SDL_Rect srcRect, destRect;

    std::vector<Equipment*> equipmentList;

    EquipmentSlot* equipSlot = new EquipmentSlot[MAX_EQUIPMENT_SLOTS];

    Label* characterInformationTitle;

    /*
    Label* information;
    Label* name, playerClass, level, guild, health, mana, exp, premium;

    Label* attribute;
    Label* strength, dexterity, intelligence, vitality, agility;

    Label* avaliblePoints, pointsText;
    */
    Button* closeButton;
};

#endif // CharacterInformation_h

