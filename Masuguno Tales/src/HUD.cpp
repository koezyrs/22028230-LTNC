#include "HUD.h"
#include "Actor.h"

HUD::HUD()
{
    SDL_Color White = {255,255,255};
    HUDBase = TextureManager::LoadTexture("data files/graphics/gui/HUDBase.png");
    HUDBars = TextureManager::LoadTexture("data files/graphics/gui/HUDBars.png");
    playerName = new Label("data files/font/game.ttf", "TunDuong" ,10,370, 485, White, 120, false, []{});
    playerLevel = new Label("data files/font/game.ttf", "Level 1",10,550,485, White, 120, false, []{});
    playerHP = new Label("data files/font/game.ttf", "100/100",10,370,503, White, 120, false, []{});
    playerMP = new Label("data files/font/game.ttf", "30/30",10,570,503, White, 120, false, []{});
    playerExperience = new Label("data files/font/game.ttf", "0/100",10,495,495, White, 120, false, []{});

    BaseSrcRect = {0,0,365,48};
    BaseDestRect = {329,478,365,48};

    HPSrcRect = {0,0,172,22};
    HPDestRect = {329,501,172,22};

    MPSrcRect = {0,26,172,22};
    MPDestRect = {524,501,172,22};
}

HUD::~HUD()
{
    delete playerName;
    delete playerLevel;
    delete playerHP;
    delete playerMP;
    delete playerExperience;

    SDL_DestroyTexture(HUDBars);
    SDL_DestroyTexture(HUDBase);

    HUDBars = NULL;
    HUDBase = NULL;
}
