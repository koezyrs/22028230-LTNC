#pragma once
#ifndef ColliderComponent_h
#define ColliderComponent_h

#include <string>
#include <SDL.h>

#include "../Game.h"
#include "TransformComponent.h"

class ColliderComponent
{
public:

    TransformComponent* mTransform;
    SDL_Rect mCollider;
    std::string tag;
    ColliderComponent(TransformComponent* trans);
    ColliderComponent(TransformComponent* trans, std::string _tag);
    void Update();
};

#endif // ColliderComponent_h
