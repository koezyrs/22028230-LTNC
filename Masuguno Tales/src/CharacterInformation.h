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
#include "Actor.h"

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
                if(EventManager::AddEquipmentToInventory(equipment))
                {
                    std::cout << "You have unequip the " << equipment->equipmentName << "!" << std::endl;
                    equipment->destroy();
                    Reset();
                }

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

    void Render() override
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

    bool AddEquipment(Equipment* _equipment);
private:
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* CharacterInformationBox;
    SDL_Rect srcRect, destRect;

    std::vector<Equipment*> equipmentList;

    EquipmentSlot* equipSlot = new EquipmentSlot[MAX_EQUIPMENT_SLOTS];

    Label* characterInformationTitle;

    Label *name, *playerClass, *level, *damage, *defense, *health, *mana, *attackSpeed;

    Label *strength, *dexterity, *intelligence, *vitality, *agility;

    //Label* avaliblePoints, pointsText;

    std::string LevelStr, DamageStr, DefenseStr, HPStr, MPStr, ASStr;
    std::string strengthStr, dexterityStr, intelligenceStr, vitalityStr, agilityStr;
    Button* closeButton;
};

#endif // CharacterInformation_h

