#include "Hotbar.h"
#include "TextureManager.h"

Hotbar::Hotbar()
{
    HotbarTex = TextureManager::LoadTexture("data files/graphics/gui/Hotbar.png");
    srcRect = {0,0,376,36};
    destRect = {324,528,376,36};
}

Hotbar::~Hotbar()
{
    SDL_DestroyTexture(HotbarTex);
    HotbarTex = NULL;
}
