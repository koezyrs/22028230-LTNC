#include <SDL_ttf.h>
#include "TextureManager.h"
SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(filename);
    if(tempSurface == NULL){
        std::cout << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
    }
    SDL_Texture* Texture = NULL;
    Texture = SDL_CreateTextureFromSurface(Game::gRenderer, tempSurface);
    if(Texture == NULL){
        std::cout << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(tempSurface);
    return Texture;
}

SDL_Texture* TextureManager::LoadText(TTF_Font* font,const char* text, SDL_Color textColor, Uint32 wrapLength)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = TTF_RenderText_Blended_Wrapped(font, text, textColor, wrapLength);
    if(tempSurface == NULL)
    {
        std::cout << "Unable to load text! TTF_Error: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* Texture = NULL;
    Texture = SDL_CreateTextureFromSurface(Game::gRenderer, tempSurface);
    if(Texture == NULL)
    {
        std::cout << "Unable to create text from surface! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(tempSurface);
    return Texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
    SDL_RenderCopy(Game::gRenderer, texture, &srcRect, &destRect);
}
