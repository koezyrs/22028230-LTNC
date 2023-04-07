#pragma once
#ifndef Monster_h
#define Monster_h

#include "Game.h"
#include "Actor.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Component/Component.h"
#include "Component/AIComponent.h"
#include "Collision.h"
#include "TextureManager.h"

class Monster : public Entity
{
public:
    Monster(float _x, float _y, int _width, int _height, int _scale,  std::string _monsterName,
                 std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                 float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed);
    ~Monster();
    void Update() override
    {
        // Check if HP <= 0
        if(health <= 0) {
            destroy();
            Game::gPlayer->getKeyboardController()->setTarget(nullptr);
            return;
        }

        // Update component
        Vector2D monsterPos = mTransform->position;
        mAI->Update();
        mTransform->Update();
        if(Collision::AABB(*mCollider, *Game::gPlayer->getColliderComponent()))
        {
            mTransform->position = monsterPos;
        }
        mCollider->Update();
        mSprite->Update();
        mName->Update();

        // HP Bar
        if(trigger)
        {
            hpDestRectBack.x = static_cast<int>(mTransform->position.x - Game::gCamera.x);
            hpDestRectBack.y = static_cast<int>(mTransform->position.y + 37 - Game::gCamera.y);
            hpDestRectOver.x = static_cast<int>(mTransform->position.x - Game::gCamera.x);
            hpDestRectOver.y = static_cast<int>(mTransform->position.y + 37 - Game::gCamera.y);
            hpDestRectOver.w = static_cast<int>(32 * health/maxhealth);
        }

        // Being targeted
        if(targeted)
        {
            targetedDestRect.x = static_cast<int>(mTransform->position.x + 24 - Game::gCamera.x);
            targetedDestRect.y = static_cast<int>(mTransform->position.y - 3  - Game::gCamera.y);
        }

    }
    void Render() override
    {
        mSprite->Render();
        mName->Render();
        if(trigger)
        {
            TextureManager::Draw(HPBarTexture, hpSourceRectBack, hpDestRectBack);
            TextureManager::Draw(HPBarTexture, hpSourceRectOver, hpDestRectOver);
        }

        if(targeted)
        {
            TextureManager::Draw(targetedTexture, targetedSrcRect, targetedDestRect);
        }
    }
    TransformComponent* getTransformComponent() {return mTransform;}
    ColliderComponent* getColliderComponent() {return mCollider;}
    SpriteComponent* getSpriteComponent() {return mSprite;}
    bool isActive() const {return active;}
    void setTrigger() {trigger = true;}
    void destroy() {active = false;}
    void ApplyDamage(float _damage);
    float getHP() {return health;}
    float getMaxHP() {return maxhealth;}
    void setTargeted() {targeted = true;}
    void unTargeted() {targeted = false;}
    bool isTargeted() {return targeted;}
private:
    Vector2D startPosition;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;
    AIComponent* mAI;

    bool active = true;
    bool trigger = false;
    bool targeted = false;

    std::string monsterName;
    std::string monsterSprite;
    float damage, health, maxhealth, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;

    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];

    // HPBar under monster
    SDL_Texture* HPBarTexture;
    SDL_Rect hpSourceRectBack, hpDestRectBack, hpSourceRectOver, hpDestRectOver;

    // Targeted icon
    SDL_Texture* targetedTexture;
    SDL_Rect targetedSrcRect, targetedDestRect;
};

#endif // Monster_h
