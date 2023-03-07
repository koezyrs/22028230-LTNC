#pragma once
#ifndef KeyboardController_h
#define KeyboardController_h

#include "../Game.h"
#include "Component.h"

class KeyboardController
{
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
public:
    KeyboardController();
    KeyboardController(TransformComponent* trans, SpriteComponent* sprite)
    {
        mSprite = sprite;
        mTransform = trans;
    }
    void Update()
    {
        if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
        {
            mSprite->isIdle = false;
            switch(Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                mTransform->velocity.y -= mTransform->speed;
                mSprite->Play("Up");
                break;
            case SDLK_DOWN:
                mTransform->velocity.y += mTransform->speed;
                mSprite->Play("Down");
                break;
            case SDLK_LEFT:
                mTransform->velocity.x -= mTransform->speed;
                mSprite->Play("Left");
                break;
            case SDLK_RIGHT:
                mTransform->velocity.x += mTransform->speed;
                mSprite->Play("Right");
                break;
            default:
                break;
            }
        }

        if(Game::event.type == SDL_KEYUP && Game::event.key.repeat == 0)
        {
            switch(Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                mTransform->velocity.y += mTransform->speed;
                break;
            case SDLK_DOWN:
                mTransform->velocity.y -= mTransform->speed;
                break;
            case SDLK_LEFT:
                mTransform->velocity.x += mTransform->speed;
                break;
            case SDLK_RIGHT:
                mTransform->velocity.x -= mTransform->speed;
                break;
            default:
                break;
            }
        }

        if(mTransform->velocity == Vector2D{0.0f,0.0f}) mSprite->isIdle = true;
    }
};

#endif // KeyboardController_h
