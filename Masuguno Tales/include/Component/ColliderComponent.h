#pragma once
#ifndef ColliderComponent_h
#define ColliderComponent_h

#include <string>
#include <SDL.h>
#include "Component.h"

class ColliderComponent
{
public:

    SDL_Rect collider;
    std::string tag;
    TransformComponent* mTransform;

    ColliderComponent(TransformComponent* trans)
    {
        mTransform = trans;
        tag = "";
    }

    ColliderComponent(TransformComponent* trans, std::string _tag)
    {
        mTransform = trans;
        tag = _tag;
    }

    void Update()
    {
        collider.x = (int)(mTransform->position.x);
        collider.y = (int)(mTransform->position.y);
        collider.w = mTransform->width * mTransform->scale;
        collider.h = mTransform->height * mTransform->scale;
    }

};

#endif // ColliderComponent_h
