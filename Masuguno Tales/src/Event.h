#pragma once
#ifndef Event_h
#define Event_h

#include <iostream>
#include <functional>
#include "Game.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Settings.h"
class Event
{
public:
    Event(float x, float y, std::function<void()> func = []{});
    virtual ~Event();
    void Update();
    void Perform();
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    bool isActive();
    void destroy();
    int map_id;
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
    std::function<void()> EventFunction;
};

#endif // Event_h
