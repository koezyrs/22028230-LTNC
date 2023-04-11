#pragma once
#ifndef Monster_h
#define Monster_h

#include "Game.h"
#include "Actor.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Component/SpriteComponent.h"
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
    void Update() override;
    void Render() override;
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    SpriteComponent* getSpriteComponent();
    bool isActive() const;
    void setTrigger();
    void destroy();
    void ApplyDamage(float _damage);
    float getHP();
    float getMaxHP();
    void setTargeted();
    void unTargeted();
    bool isTargeted();
    std::string getMonsterName();
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
