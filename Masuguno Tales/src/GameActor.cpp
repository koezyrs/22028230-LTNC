#include "../include/GameActor.h"

GameActor::GameActor() : Entity::Entity()
{
    mTransform = new TransformComponent(0, 0, 32, 48, 1);
    mSprite = new SpriteComponent("assets/player.png", mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite);
    Game::gGroupPlayers.push_back(this);
}

GameActor::~GameActor()
{
    delete mController;
    delete mTransform;
    delete mSprite;
    delete mCollider;
}
