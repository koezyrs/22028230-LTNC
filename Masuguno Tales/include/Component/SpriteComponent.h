#pragma once
#ifndef SpriteComponent_h
#define SpriteComponent_h

#include "SDL.h"
#include "Component.h"
#include "../TextureManager.h"

class SpriteComponent
{
private:
    TransformComponent* mTransform;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent();
    SpriteComponent(const char* path, TransformComponent* trans)
    {
        mTexture = TextureManager::LoadTexture(path);
        mTransform = trans;
        srcRect.x = srcRect.y = 0;
        srcRect.w = mTransform->width;
        srcRect.h = mTransform->height;
    }
    ~SpriteComponent()
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }

    void Update()
    {
        destRect.x = (int)mTransform->position.x;
        destRect.y = (int)mTransform->position.y;
        destRect.w = mTransform->width * mTransform->scale;
        destRect.h = mTransform->height * mTransform->scale;
    }

    void Render()
    {
        TextureManager::Draw(mTexture, srcRect, destRect);
    }
};

#endif // SpriteComponent_h
