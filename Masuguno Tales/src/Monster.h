#pragma once
#ifndef Monster_h
#define Monster_h

#include "Vector2D.h"
#include "Entity.h"
#include "Component/Component.h"
#include "Component/AIComponent.h"

class Monster : public Entity
{
public:
    Monster(float _x, float _y, int _width, int _height, int _scale, const char* filepath, std::string name, int _speed);
    ~Monster();
    void Update() override
    {
        //mTransform->position.x = position.x;
        //mTransform->position.y = position.y;
        mAI->Update();
        mTransform->Update();
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
    void destroy() {active = false;}
private:
    Vector2D position;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;
    AIComponent* mAI;

    bool active = true;
    float speed;

    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // Monster_h
