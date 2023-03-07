#include "../include/GameActor.h"

GameActor::GameActor() : Entity::Entity()
{
    mTransform = new TransformComponent(100, 100, PLAYER_WIDTH, PLAYER_HEIGHT, 1);
    mSprite = new SpriteComponent("assets/player.png", mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite);
}

GameActor::~GameActor()
{
    delete mController;
    delete mTransform;
    delete mSprite;
    delete mCollider;
}
