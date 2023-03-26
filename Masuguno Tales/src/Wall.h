#pragma once
#ifndef Wall_h
#define Wall_h

#include "Vector2D.h"
#include "Entity.h"
#include "Component/Component.h"
#include "Settings.h"

class Wall : public Entity
{
public:
    Wall(float x, float y);
    ~Wall();

    void Update() override
    {
        mTransform->position.x = position.x;
        mTransform->position.y = position.y;
        mCollider->Update();
    }

    void Render() override
    {
    }
    Vector2D getPosition() {return position;}
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
#endif // Wall_h
