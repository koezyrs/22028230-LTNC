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
            switch(Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                mTransform->velocity.y -= mTransform->speed;
                break;
            case SDLK_DOWN:
                mTransform->velocity.y += mTransform->speed;
                break;
            case SDLK_LEFT:
                mTransform->velocity.x -= mTransform->speed;
                break;
            case SDLK_RIGHT:
                mTransform->velocity.x += mTransform->speed;
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
    }
};

#endif // KeyboardController_h
