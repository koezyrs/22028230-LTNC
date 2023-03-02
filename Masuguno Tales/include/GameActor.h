#pragma once

#ifndef GameActor_h
#define GameActor_h

#include "Game.h"
#include "Entity.h"
#include "TextureManager.h"
#include "Component/Component.h"
#include "Vector2D.h"
#include "config.h"

class GameActor : public Entity
{
public:
    GameActor();
    ~GameActor();
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


