#include "../include/GameActor.h"

GameActor::GameActor()
{
    mTransform = new TransformComponent(0, 0, 32, 48, 1);
    mSprite = new SpriteComponent("assets/player.png", mTransform);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform);
}

GameActor::~GameActor()
{
    delete mController;
    delete mTransform;
    delete mSprite;
    delete mCollider;
}

void GameActor::Update()
{
    mController->Update();
    mTransform->Update();
    mCollider->Update();
    mSprite->Update();
}

void GameActor::Render()
{
     mSprite->Render();
}
