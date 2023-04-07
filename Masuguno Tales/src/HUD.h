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
            string LevelStr = "Level " + to_string(Game::gPlayer->mStats->Level);
            string HPStr = to_string(Game::gPlayer->mStats->Health) + "/" + to_string(Game::gPlayer->mStats->MaxHealth);
            string MPStr = to_string(Game::gPlayer->mStats->Mana) + "/" + to_string(Game::gPlayer->mStats->MaxMana);
            string EXPStr = to_string(Game::gPlayer->mStats->Experience) + "/" + to_string(Game::gPlayer->mStats->ExperienceToNextLevel);
        //Update player status here
            SDL_Color White = {255,255,255};
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
        }
        playerLevel->Render();
        playerName->Render();
        playerHP->Render();
        playerMP->Render();
        playerExperience->Render();
    }

private:
    Monster* target;

    SDL_Texture* HUDBase;
    SDL_Texture* HUDBars;
    SDL_Texture* TargetHP;

    SDL_Rect BaseSrcRect, BaseDestRect;
    SDL_Rect HPSrcRect, HPDestRect;
    SDL_Rect MPSrcRect, MPDestRect;
    SDL_Rect TargetHPSrcRectBack, TargetHPDestRectBack, TargetHPSrcRectOver, TargetHPDestRectOver;

    Label* playerName;
    Label* playerLevel;
    Label* playerExperience;
    Label* playerHP;
    Label* playerMP;
};

#endif // HUD_h
