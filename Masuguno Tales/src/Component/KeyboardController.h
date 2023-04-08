#pragma once
#ifndef KeyboardController_h
#define KeyboardController_h

#include <vector>

#include "../Game.h"
#include "Component.h"
#include "../Entity.h"
#include "../Vector2D.h"
#include "../EventManager.h"
#include "../Database/SkillDB.h"

class Monster;

class KeyboardController
{
private:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    Monster* target;
    Uint64 cooldownBasicAttack;
public:
    KeyboardController();
    KeyboardController(TransformComponent* trans, SpriteComponent* sprite)
    : cooldownBasicAttack(0)
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
                {
                    EventManager::setNearestTarget();
                    break;
                }

            case SDLK_LCTRL:
                {
                    SkillType sk = SkillDB::skillDatabase["BasicAttack"];
                    if(SDL_GetTicks64() > cooldownBasicAttack)
                    {
                        if(EventManager::PerformSkill(target, mTransform->position, "BasicAttack"))
                        {
                            cooldownBasicAttack = SDL_GetTicks64() + sk.cooldown;
                            EventManager::SetSystemMessage(" ", 0);
                        }
                    }else
                    {
                        std::string _message = "Wait " +  to_string((float)(cooldownBasicAttack - SDL_GetTicks64())/1000) + "s for the next attack!";
                        EventManager::SetSystemMessage(_message, 2000);
                    }
                    break;
                }

            case SDLK_1:
                {
                    break;
                }

            }
        }

    }
};

#endif // KeyboardController_h
