#pragma once
#ifndef Event_h
#define Event_h

#include "Game.h"
#include "Component/Component.h"
class Event
{
public:
    Event(float x, float y);
    virtual ~Event();
    virtual void Perform() = 0;
    void Update()
    {
        mTransform->position.x = position.x - Game::gCamera.x;
        mTransform->position.y = position.y - Game::gCamera.y;
        mCollider->Update();
    }
    TransformComponent* getTransformComponent() {return mTransform;}
    ColliderComponent* getColliderComponent() {return mCollider;}
    bool isActive() {return active;}
    void destroy() {active = false;}
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
};

#endif // Event_h
