#pragma once
#ifndef HUD_h
#define HUD_h

#include "Game.h"
#include "TextureManager.h"
#include "Label.h"
#include "Actor.h"

class HUD
{
public:
    HUD();
    ~HUD();
    void Update()
    {
        //Update player status here

        //HPBar
            HPSrcRect.w = static_cast<int>(172 * static_cast<float>(Game::gPlayer->mStats->getHealth()) / static_cast<float>(Game::gPlayer->mStats->getMaxHealth()));
            HPDestRect.w = HPSrcRect.w;
        //MPBar
            MPDestRect.w = MPSrcRect.w = static_cast<int>(172 * static_cast<float>(Game::gPlayer->mStats->getMana()) / static_cast<float>(Game::gPlayer->mStats->getMaxMana()));
            MPSrcRect.x = 172 - MPSrcRect.w;
            MPDestRect.x = 524 + MPSrcRect.x;
    }
    void Render()
    {
        TextureManager::Draw(HUDBase, BaseSrcRect,BaseDestRect);
        TextureManager::Draw(HUDBars, HPSrcRect, HPDestRect);
        TextureManager::Draw(HUDBars, MPSrcRect, MPDestRect);
        playerLevel->Render();
        playerName->Render();
        playerHP->Render();
        playerMP->Render();
        playerExperience->Render();
    }

private:
    SDL_Texture* HUDBase;
    SDL_Texture* HUDBars;

    SDL_Rect BaseSrcRect, BaseDestRect;
    SDL_Rect HPSrcRect, HPDestRect;
    SDL_Rect MPSrcRect, MPDestRect;

    Label* playerName;
    Label* playerLevel;
    Label* playerExperience;
    Label* playerHP;
    Label* playerMP;
};

#endif // HUD_h
