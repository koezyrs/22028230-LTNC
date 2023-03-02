#pragma once
#ifndef ColliderComponent_h
#define ColliderComponent_h

#include <string>
#include <SDL.h>
#include "Component.h"

class ColliderComponent
{
public:

    TransformComponent* mTransform;
    SDL_Rect mCollider;
    std::string tag;

    ColliderComponent(TransformComponent* trans)
    {
        mTransform = trans;
        tag = "";
        Game::gGroupColliders.push_back(this);
    }

    ColliderComponent(TransformComponent* trans, std::string _tag)
    {
        mTransform = trans;
        tag = _tag;
        Game::gGroupColliders.push_back(this);
    }

    void Update()
    {
        mCollider.x = static_cast<int>(mTransform->position.x);
        mCollider.y = static_cast<int>(mTransform->position.y);
        mCollider.w = mTransform->width * mTransform->scale;
        mCollider.h = mTransform->height * mTransform->scale;
    }

};

#endif // ColliderComponent_h
