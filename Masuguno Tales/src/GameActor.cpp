#include "../include/GameActor.h"

GameActor::GameActor(int x, int y, const char* texturesheet)
{
    mTransform = new TransformComponent(0,0);
    mController = new KeyboardController(mTransform);
    objTexture = TextureManager::LoadTexture(texturesheet);

    // Move down animation
    mSpriteMoveDown[0] = {0, 0, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveDown[1] = {32, 0, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveDown[2] = {64, 0, PLAYER_PIXELS, PLAYER_PIXELS + 16};

    // Move left animation
    mSpriteMoveLeft[0] = {0, 48, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveLeft[1] = {32, 48, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveLeft[2] = {64, 48, PLAYER_PIXELS, PLAYER_PIXELS + 16};

    // Move right animation
    mSpriteMoveRight[0] = {0, 96, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveRight[1] = {32, 96, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveRight[2] = {64, 96, PLAYER_PIXELS, PLAYER_PIXELS + 16};

    // Move up animation
    mSpriteMoveUp[0] = {0, 144, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveUp[1] = {32, 144, PLAYER_PIXELS, PLAYER_PIXELS + 16};
    mSpriteMoveUp[2] = {64, 144, PLAYER_PIXELS, PLAYER_PIXELS + 16};

    currentSprite = mSpriteMoveDown[1];
}

GameActor::~GameActor()
{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}


void GameActor::Update()
{
    mController->Update();
    mTransform->Update();
}

void GameActor::Render()
{
     destRect.x = (int)mTransform->position.x;
     destRect.y = (int)mTransform->position.y;
     destRect.w = currentSprite.w * 2;
     destRect.h = currentSprite.h * 2;
     SDL_RenderCopy(Game::gRenderer, objTexture, &currentSprite, &destRect);
}
