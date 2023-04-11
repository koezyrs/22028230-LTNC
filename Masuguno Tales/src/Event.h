#pragma once
#ifndef Event_h
#define Event_h

#include <iostream>
#include "Game.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "EventManager.h"
#include "Settings.h"
class Event
{
public:
    Event(float x, float y);
    virtual ~Event();
    virtual void Perform() = 0;
    void Update();
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    bool isActive();
    void destroy();
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
};

#endif // Event_h
