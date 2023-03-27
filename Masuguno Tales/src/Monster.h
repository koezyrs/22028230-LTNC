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
    Monster(float _x, float _y, int _width, int _height, int _scale, const char* filepath, std::string name, float _speed);
    ~Monster();
    void Update() override
    {
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
private:
    Vector2D startPosition;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;
    AIComponent* mAI;

    bool active = true;
    bool trigger = false;
    float speed;

    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // Monster_h
