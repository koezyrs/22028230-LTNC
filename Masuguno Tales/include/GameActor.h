#pragma once

#ifndef GameActor_h
#define GameActor_h

#include "Game.h"
#include "TextureManager.h"
#include "Component/Component.h"
#include "Vector2D.h"
#include "config.h"

class GameActor
{
public:
    GameActor(int x, int y, const char* texturesheet = NULL);
    ~GameActor();
    void Update();
    void Render();
    bool isActive() const {return active;}
    void destroy() {active = false;}
private:
    TransformComponent* mTransform;
    KeyboardController* mController;
    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
    bool active = true;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif // GameObject_h


