#pragma once
#ifndef NPC_h
#define NPC_h

#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

#include "Vector2D.h"
#include "Entity.h"
#include "Component/Component.h"
#include "Dialogue.h"

class NPC : public Entity
{
    public:
    NPC(float _x, float _y, int _width, int _height, int _scale, const char* filepath, std::string name);
    ~NPC();
    void Update() override
    {
        mTransform->position.x = position.x;
        mTransform->position.y = position.y;
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
    NameComponent* getNameComponent() {return mName;}
    void PlayDialogue();
    void HideDialogue();
    bool isInteract = false;
    bool isActive() const {return active;}
    void destroy() {active = false;}
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;

    std::string npcName;
    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // NPC_h
