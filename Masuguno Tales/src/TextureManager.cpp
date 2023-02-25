#include "../include/TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(filename);
    if(tempSurface == NULL){
        cout << "Unable to load image! IMG_Error: " << IMG_GetError() << endl;
    }
    SDL_Texture* Texture = NULL;
    Texture = SDL_CreateTextureFromSurface(Game::gRenderer, tempSurface);
    if(Texture == NULL){
        cout << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << endl;
    }
    SDL_FreeSurface(tempSurface);
    return Texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
    SDL_RenderCopy(Game::gRenderer, texture, &srcRect, &destRect);
}
