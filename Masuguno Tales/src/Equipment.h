#pragma once
#ifndef Equipment_h
#define Equipment_h

#include <SDL.h>
#include <string>
#include <functional>

#include "TextureManager.h"
#include "Settings.h"

class Equipment
{
public:
    Equipment(int _id, std::string spriteName, EQUIPMENT_TAG _equipmentTag, std::string _equipmentName, int _maxHealth, int _maxMana, int _damage, int _defense, int _attackSpeed);
    ~Equipment();
    SDL_Texture* getEquipmentSprite();
    bool isActive();
    void destroy();
    int id;
    EQUIPMENT_TAG equipmentTag;
    const char* description;
    std::string equipmentName;
    int MaxHealth = 0;
    int MaxMana = 0;
    int Damage = 0;
    int Defense = 0;
    int AttackSpeed = 0;
private:
    bool active = true;
    SDL_Texture* equipmentSprite;;
};

#endif // Equipment
