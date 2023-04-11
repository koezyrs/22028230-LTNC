#include "Equipment.h"

Equipment::Equipment(int _id, std::string spriteName, EQUIPMENT_TAG _equipmentTag, std::string _equipmentName, int _maxHealth, int _maxMana, int _damage, int _defense, int _attackSpeed)
: id(_id), equipmentTag(_equipmentTag), equipmentName(_equipmentName), MaxHealth(_maxHealth), MaxMana(_maxMana), Damage(_damage), Defense(_defense), AttackSpeed(_attackSpeed)
{
    equipmentSprite = TextureManager::GetTexture(spriteName);
}

Equipment::~Equipment()
{
    equipmentSprite = NULL;
}

SDL_Texture* Equipment::getEquipmentSprite()
{
    return equipmentSprite;
}
bool Equipment::isActive()
{
    return active;
}
void Equipment::destroy()
{
    active = false;
}
