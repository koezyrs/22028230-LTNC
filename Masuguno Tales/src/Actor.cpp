#include "../include/Actor.h"

Actor::Actor(float x, float y, const char* filetex) : Entity::Entity()
{
    mTransform = new TransformComponent(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, 1);
    mSprite = new SpriteComponent(filetex, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite);
}

Actor::~Actor()
{
    delete mController;
    delete mTransform;
    delete mSprite;
    delete mCollider;
}
