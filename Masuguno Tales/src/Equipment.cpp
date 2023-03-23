#include "Equipment.h"
#include "TextureManager.h"

Equipment::Equipment(int _id, const char* spritePath, EQUIPMENT_TAG _equipmentTag, std::string _equipmentName, int _maxHealth, int _maxMana, int _damage, int _defense, int _attackSpeed)
: id(_id), equipmentTag(_equipmentTag), equipmentName(_equipmentName), MaxHealth(_maxHealth), MaxMana(_maxMana), Damage(_damage), Defense(_defense), AttackSpeed(_attackSpeed)
{
    equipmentSprite = TextureManager::LoadTexture(spritePath);
}

Equipment::~Equipment()
{
    SDL_DestroyTexture(equipmentSprite);
    equipmentSprite = NULL;
}
