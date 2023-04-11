#include "KeyboardController.h"

#include "../Map.h"
#include "../Actor.h"
#include "../HUD.h"

KeyboardController::KeyboardController() {}
KeyboardController::KeyboardController(TransformComponent* trans, SpriteComponent* sprite)
: cooldownBasicAttack(0), state(NONE)
{
    mSprite = sprite;
    mTransform = trans;
    target = nullptr;
}

Monster* KeyboardController::getTarget()
{
    return target;
}

void KeyboardController::setTarget(Monster* _tar) {
    target = _tar;
}

void KeyboardController::setNearestTarget()
{
    int distanceToNearestTarget = 320; // Scan radious
    Vector2D playerPos = Game::gPlayer->getTransformComponent()->position;
    for(auto& monster : Game::currentMap->monsters)
    {
        Vector2D monsterPos = monster->getTransformComponent()->position;
        int distance = playerPos.DistanceTo(monsterPos);
        if(distance < distanceToNearestTarget)
        {
            distanceToNearestTarget = distance;
            if(target != nullptr) target->unTargeted();
            target = monster;
            target->setTargeted();
        }
    }
    if(distanceToNearestTarget == 320)
    {
        if(target != nullptr) target->unTargeted();
        target = nullptr;
    }
}

void KeyboardController::PerformSkill(std::string skillDatabaseName, Uint64 &_cooldown)
{
    if(target == nullptr) return;
    SkillType sk = SkillDB::skillDatabase[skillDatabaseName];
    if(sk.skillName.empty())
    {
        std::cerr << "No skill as " << skillDatabaseName << "! Please check Skill Database" << std::endl;
        return;
    }

    if(SDL_GetTicks64() <= _cooldown)
    {
        std::string _message = "Wait " +  to_string((float)(_cooldown - SDL_GetTicks64())/1000) + "s for the next attack!";
        Game::gHUD->setSystemMessage(_message, 2000);
        return;
    }

    // Attack Monster
    bool success = false;
    Vector2D monsterPos = target->getTransformComponent()->position;
    Vector2D currentplayerPos = mTransform->position;
    float distance = sqrt((monsterPos.x - currentplayerPos.x)*(monsterPos.x - currentplayerPos.x) + (monsterPos.y - currentplayerPos.y)*(monsterPos.y - currentplayerPos.y));
    float skillRange = sk.skillRange;
    if( (distance <= skillRange) && (target->isTargeted()) )
    {
        float offsetX = 32;
        float offsetY = 32;
        target->setTrigger();
        Game::currentMap->AddProjectile(monsterPos.x - offsetX, monsterPos.y - offsetY, sk.skillFrames, sk.skillSprite, sk.damage);
        success = true;
    }

    if(!success) return;
    _cooldown = SDL_GetTicks64() + sk.cooldown;
    Game::gHUD->setSystemMessage(" ", 0);
}

void KeyboardController::Update()
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
        }
    }

    if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
    {
        switch(Game::event.key.keysym.sym)
        {
        case SDLK_TAB:
            {
                setNearestTarget();
                break;
            }

        case SDLK_LCTRL:
            {
                PerformSkill("BasicAttack", cooldownBasicAttack);
                break;
            }

        case SDLK_1:
            {
                break;
            }

        }
    }

}
