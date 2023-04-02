#pragma once
#ifndef SpriteComponent_h
#define SpriteComponent_h

#include <map>
#include <SDL.h>
#include "Component.h"
#include "../TextureManager.h"
#include "../Animation.h"

class SpriteComponent
{
private:
    TransformComponent* mTransform;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    int animIndex = 0;
    bool isIdle = true;
    std::map<const char*, Animation> animations;

    SpriteComponent();
    SpriteComponent(std::string spriteName, TransformComponent* trans)
    {
        mTexture = TextureManager::GetTexture(spriteName);
        mTransform = trans;
        srcRect.x = srcRect.y = 0;
        srcRect.w = mTransform->width;
        srcRect.h = mTransform->height;
    }

    SpriteComponent(std::string spriteName, TransformComponent* trans, bool isAnimated)
    {
        animated = isAnimated;

        Animation walkDown = Animation(0, 3, 200);
        Animation walkLeft = Animation(1, 3, 200);
        Animation walkRight = Animation(2, 3, 200);
        Animation walkUp = Animation(3, 3, 200);

        animations.emplace("Down", walkDown);
        animations.emplace("Left", walkLeft);
        animations.emplace("Right", walkRight);
        animations.emplace("Up", walkUp);

        Play("Down");

        mTexture = TextureManager::GetTexture(spriteName);
        mTransform = trans;
        srcRect.x = srcRect.y = 0;
        srcRect.w = mTransform->width;
        srcRect.h = mTransform->height;
    }


    ~SpriteComponent()
    {
        mTexture = NULL;
    }

    void Update()
    {
        if(animated)
        {
            isIdle = false;
            if(mTransform->velocity.y == mTransform->speed && mTransform->velocity.x == 0) Play("Down");
            else if(mTransform->velocity.y == -mTransform->speed && mTransform->velocity.x == 0) Play("Up");
            else if(mTransform->velocity.y == 0 && mTransform->velocity.x == mTransform->speed) Play("Right");
            else if(mTransform->velocity.y == 0 && mTransform->velocity.x == -mTransform->speed) Play("Left");
            else if(mTransform->velocity.y == mTransform->speed && mTransform->velocity.x == mTransform->speed) Play("Down");
            else if(mTransform->velocity.y == mTransform->speed && mTransform->velocity.x == -mTransform->speed) Play("Down");
            else if(mTransform->velocity.y == -mTransform->speed && mTransform->velocity.x == mTransform->speed) Play("Up");
            else if(mTransform->velocity.y == -mTransform->speed && mTransform->velocity.x == -mTransform->speed) Play("Up");
            if(mTransform->velocity == Vector2D{0.0f,0.0f}) isIdle = true;

            if(isIdle) srcRect.x = srcRect.w; // The middle animation
            else srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        srcRect.y = animIndex * mTransform->height;

        destRect.x = static_cast<int>(mTransform->position.x) - Game::gCamera.x;
        destRect.y = static_cast<int>(mTransform->position.y) - Game::gCamera.y;
        destRect.w = mTransform->width * mTransform->scale;
        destRect.h = mTransform->height * mTransform->scale;
    }

    void Render()
    {
        TextureManager::Draw(mTexture, srcRect, destRect);
    }

    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};

#endif // SpriteComponent_h
