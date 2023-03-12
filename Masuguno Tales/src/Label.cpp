#include "Label.h"
#include "TextureManager.h"

Label::Label(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor)
: position(x,y)
{
    font = TTF_OpenFont(fontFile, fontSize);
    text = TextureManager::LoadText(font, textContent, textColor);
    SDL_QueryTexture(text, NULL, NULL, &Width, &Heigth);
    srcRect.x = srcRect.y = 0;
    destRect.x = position.x;
    destRect.y = position.y;

    srcRect.w = destRect.w = Width;
    srcRect.h = destRect.h = Heigth;
}

Label::~Label()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(text);
    font = NULL;
    text = NULL;
}

void Label::Render()
{
    TextureManager::Draw(text, srcRect, destRect);
}
