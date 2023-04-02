#include "Hotbar.h"
#include "TextureManager.h"

Hotbar::Hotbar()
{
    HotbarTex = TextureManager::GetTexture("Hotbar");
    srcRect = {0,0,376,36};
    destRect = {324,528,376,36};
}

Hotbar::~Hotbar()
{
    HotbarTex = NULL;
}
