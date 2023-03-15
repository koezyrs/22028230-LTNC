#pragma once

#ifndef Actor_h
#define Actor_h

#include <SDL.h>
#include "Game.h"
#include "Entity.h"
#include "TextureManager.h"
#include "Component/Component.h"
#include "Vector2D.h"
#include "Settings.h"
#include "Inventory.h"

class Actor : public Entity
{
public:
    Actor(float x, float y, const char* filetex);
    ~Actor();
    void Update() override
    {
        mController->Update();
        mTransform->Update();
        mCollider->Update();
        mSprite->Update();
        mName->Update();
        mInventory->Update();
    }
    void Render() override
    {
        mSprite->Render();
        mName->Render();
        mInventory->Render();
    }
    TransformComponent* getTransformComponent() {return mTransform;}
    ColliderComponent* getColliderComponent() {return mCollider;}
    KeyboardController* getKeyboardController() {return mController;}
    SpriteComponent* getSpriteComponent() {return mSprite;}
    NameComponent* getNameComponent() {return mName;}
    Inventory* getInventory() {return mInventory;}
    StatsComponent* mStats;
    bool isActive() const {return active;}
    void destroy() {active = false;}
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    KeyboardController* mController;
    NameComponent* mName;

    Inventory* mInventory;

    bool active = true;
    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // GameObject_h


