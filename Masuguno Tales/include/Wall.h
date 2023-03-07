#pragma once
#ifndef Wall_h
#define Wall_h

#include "Vector2D.h"
#include "Entity.h"
#include "Component/Component.h"
#include "config.h"

class Wall : public Entity
{
public:
    Wall(float x, float y);
    ~Wall();

    void Update() override
    {
        mTransform->position.x = position.x - Game::gCamera.x;
        mTransform->position.y = position.y - Game::gCamera.y;
        mCollider->Update();
    }

    void Render() override
    {
    }
    bool isActive() {return active;}
    void destroy() {active = false;}
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
};
#endif // Wall_h
