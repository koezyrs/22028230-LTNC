#pragma once

#ifndef Actor_h
#define Actor_h

#include <SDL.h>
#include <string>
#include "Game.h"
#include "Entity.h"
#include "TextureManager.h"

// Component
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Component/KeyboardController.h"
#include "Component/SpriteComponent.h"
#include "Component/NameComponent.h"
#include "Component/StatsComponent.h"

#include "Vector2D.h"
#include "Settings.h"

class Actor : public Entity
{
public:
    Actor(float x, float y, std::string spriteName);
    ~Actor();
    void Update() override;
    void Render() override;
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    KeyboardController* getKeyboardController();
    SpriteComponent* getSpriteComponent();
    NameComponent* getNameComponent();

    StatsComponent* mStats;

    bool isActive() const;
    void destroy();
    void setPosition(float x, float y);

    std::map<int,int> mVariable;

private:
    bool active = true;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    KeyboardController* mController;
    NameComponent* mName;

    // Sprite Section
    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // GameObject_h


