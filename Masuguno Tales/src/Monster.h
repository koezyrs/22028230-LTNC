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
    }
    void Render() override
    {
        mSprite->Render();
        mName->Render();
    }
    TransformComponent* getTransformComponent() {return mTransform;}
    ColliderComponent* getColliderComponent() {return mCollider;}
    SpriteComponent* getSpriteComponent() {return mSprite;}
    bool isActive() const {return active;}
    void setTrigger() {trigger = true;}
    void destroy() {active = false;}
    void applyDamage(float _damage) {health -= _damage;}
private:
    Vector2D startPosition;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;
    AIComponent* mAI;

    bool active = true;
    bool trigger = false;

    std::string monsterName;
    std::string monsterSprite;
    float damage, health, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;

    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // Monster_h
