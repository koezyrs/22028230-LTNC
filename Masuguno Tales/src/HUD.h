#pragma once
#ifndef HUD_h
#define HUD_h

#include <string>

#include "Game.h"
#include "TextureManager.h"
#include "Label.h"
#include "Monster.h"
#include "Actor.h"

class HUD
{
public:
    HUD();
    ~HUD();
    void Update()
    {
        // Reset label
            playerLevel->Reset();
            playerHP->Reset();
            playerMP->Reset();
            playerExperience->Reset();
            targetName->Reset();
            targetHP->Reset();
            std::string LevelStr = "Level " + to_string(Game::gPlayer->mStats->Level);
            std::string HPStr = to_string(Game::gPlayer->mStats->Health) + "/" + to_string(Game::gPlayer->mStats->MaxHealth);
            std::string MPStr = to_string(Game::gPlayer->mStats->Mana) + "/" + to_string(Game::gPlayer->mStats->MaxMana);
            std::string EXPStr = to_string(Game::gPlayer->mStats->Experience) + "/" + to_string(Game::gPlayer->mStats->ExperienceToNextLevel);

        //Update player status here
            playerLevel = new Label("data files/font/game.ttf", LevelStr.c_str(),10,550,485, White, 120, false, []{});
            playerHP = new Label("data files/font/game.ttf", HPStr.c_str(),10,370,503, White, 120, false, []{});
            playerMP = new Label("data files/font/game.ttf", MPStr.c_str(),10,570,503, White, 120, false, []{});
            playerExperience = new Label("data files/font/game.ttf", EXPStr.c_str(),10,495,495, White, 120, false, []{});

        //HPBar
            HPSrcRect.w = static_cast<int>(172 * static_cast<float>(Game::gPlayer->mStats->Health) / static_cast<float>(Game::gPlayer->mStats->MaxHealth));
            HPDestRect.w = HPSrcRect.w;

        //MPBar
            MPDestRect.w = MPSrcRect.w = static_cast<int>(172 * static_cast<float>(Game::gPlayer->mStats->Mana) / static_cast<float>(Game::gPlayer->mStats->MaxMana));
            MPSrcRect.x = 172 - MPSrcRect.w;
            MPDestRect.x = 524 + MPSrcRect.x;

        // Target HP Bar
            target = Game::gPlayer->getKeyboardController()->getTarget();
            if(target != nullptr)
            {
                TargetHPDestRectOver.w = static_cast<int> (210* target->getHP() / target->getMaxHP());
            }

        // Target label
            if(target != nullptr)
            {
                std::string TargName = target->getMonsterName();
                std::string TargHP = to_string((int)target->getHP()) + "/" + to_string((int)target->getMaxHP());
                targetName = new Label("data files/font/game.ttf", TargName.c_str(), 10, 420, 38, Black, 120, false, []{});
                targetHP = new Label("data files/font/game.ttf", TargHP.c_str(), 10, 440, 53, White, 120, false, []{});
            }

        // System Message Label
            if(SDL_GetTicks64() > systemMessageTimeout)
            {
                systemMessage->Reset();
                systemMessage = new Label("data files/font/game.ttf", " ", 10, 460, 50, Black, 360, false, []{});
            }
    }
    void Render()
    {
        TextureManager::Draw(HUDBase, BaseSrcRect,BaseDestRect);
        TextureManager::Draw(HUDBars, HPSrcRect, HPDestRect);
        TextureManager::Draw(HUDBars, MPSrcRect, MPDestRect);
        if(target != nullptr)
        {
            TextureManager::Draw(TargetHP, TargetHPSrcRectBack, TargetHPDestRectBack);
            TextureManager::Draw(TargetHP, TargetHPSrcRectOver, TargetHPDestRectOver);
            targetName->Render();
            targetHP->Render();
        }

        // Render character label
        playerLevel->Render();
        playerName->Render();
        playerHP->Render();
        playerMP->Render();
        playerExperience->Render();

        // Render system message
        systemMessage->Render();
    }

    void setSystemMessage(std::string _message, Uint64 timeout);
private:
    // Color
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};

    // Target
    Monster* target;

    // GUI
    SDL_Texture* HUDBase;
    SDL_Texture* HUDBars;
    SDL_Texture* TargetHP;

    SDL_Rect BaseSrcRect, BaseDestRect;
    SDL_Rect HPSrcRect, HPDestRect;
    SDL_Rect MPSrcRect, MPDestRect;
    SDL_Rect TargetHPSrcRectBack, TargetHPDestRectBack, TargetHPSrcRectOver, TargetHPDestRectOver;

    // Player label UI
    Label* playerName;
    Label* playerLevel;
    Label* playerExperience;
    Label* playerHP;
    Label* playerMP;

    // Target label UI
    Label* targetName;
    Label* targetHP;

    // System label message
    Label* systemMessage;
    Uint64 systemMessageTimeout;
};

#endif // HUD_h
