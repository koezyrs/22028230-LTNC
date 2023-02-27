#pragma once
#ifndef Wall_h
#define Wall_h

#include "Game.h"
#include "Component/Component.h"
#include "TextureManager.h"

class Wall
{
public:
    Wall();
    ~Wall();
    void Update();
    void Render();
    TransformComponent* getTransformComponent() {return mTransform;}
    ColliderComponent* getColliderComponent() {return mCollider;}
    bool isActive() const {return active;}
    void destroy() {active = false;}
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    bool active = true;
};
#endif // Wall_h
