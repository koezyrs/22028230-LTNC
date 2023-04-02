
#pragma once
#ifndef Projectile_h
#define Projectile_h

#include "Game.h"
#include "Entity.h"
#include "Animation.h"
#include "Component/Component.h"
#include "Vector2D.h"

class Projectile: public Entity
{
public:
    Projectile(float _x, float _y, int _frames, int _speed, std::string _tag);
    ~Projectile();
    void Update() override
    {
        if(srcRect.x >= Width)
        {
            destroy();
            return;
        }
        currentTime = SDL_GetTicks() - startTime;
        mTransform->Update();
        mCollider->Update();
    }
    void Render() override
    {
        srcRect.x = srcRect.w * static_cast<int>((currentTime / speed) % (frames + 1));
        if(srcRect.x >= Width)
        {
            destroy();
            return;
        }
        destRect.x = static_cast<int>(mTransform->position.x) - Game::gCamera.x;
        destRect.y = static_cast<int>(mTransform->position.y) - Game::gCamera.y;
        destRect.w = 96 * mTransform->scale;
        destRect.h = 96 * mTransform->scale;
        TextureManager::Draw(mTexture, srcRect, destRect);
    }
    bool isActive() {return active;}
    void destroy() {active = false;}
private:
    bool active = true;
    Vector2D position;
    int frames, speed;
    SDL_Texture* mTexture;
    int Width, Height;
    SDL_Rect srcRect, destRect;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
    Uint32 startTime;
    Uint32 currentTime;
    std::string tag;
};

#endif // Projectile_h
