#pragma once
#ifndef KeyboardController_h
#define KeyboardController_h

#include <vector>

#include "../Game.h"
#include "Component.h"
#include "../Entity.h"
#include "../Vector2D.h"
#include "../EventManager.h"

class Monster;

class KeyboardController
{
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    Monster* target;
public:
    KeyboardController();
    KeyboardController(TransformComponent* trans, SpriteComponent* sprite)
    {
        mSprite = sprite;
        mTransform = trans;
        target = nullptr;
    }

    Monster* getTarget() {return target;}

    void setTarget(Monster* _tar) {target = _tar;}

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

        if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
        {
            switch(Game::event.key.keysym.sym)
            {
            case SDLK_TAB:
                EventManager::setNearestTarget();
                break;
            case SDLK_LCTRL:
                EventManager::PerformSkill(target, mTransform->position, "BasicAttack");
                break;
            }
        }

    }
};

#endif // KeyboardController_h
