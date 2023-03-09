#pragma once

#ifndef Actor_h
#define Actor_h

#include "Game.h"
#include "Entity.h"
#include "TextureManager.h"
#include "Component/Component.h"
#include "Vector2D.h"
#include "Config.h"

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
    }
    void Render() override
    {
        mSprite->Render();
    }
    TransformComponent* getTransformComponent() {return mTransform;}
    ColliderComponent* getColliderComponent() {return mCollider;}
    KeyboardController* getKeyboardController() {return mController;}
    SpriteComponent* getSpriteComponent() {return mSprite;}
    bool isActive() const {return active;}
    void destroy() {active = false;}
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    KeyboardController* mController;
    bool active = true;

    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // GameObject_h


