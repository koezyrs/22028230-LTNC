#pragma once
#ifndef KeyboardController_h
#define KeyboardController_h

#include <vector>

#include "../Game.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../Entity.h"
#include "../Vector2D.h"
#include "../EventManager.h"
#include "../Database/SkillDB.h"

class Monster;

class KeyboardController
{
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    Monster* target;
    Uint64 cooldownBasicAttack;
public:
    KeyboardController();
    KeyboardController(TransformComponent* trans, SpriteComponent* sprite);
    Monster* getTarget();
    void setTarget(Monster* _tar);
    void Update();
};

#endif // KeyboardController_h
