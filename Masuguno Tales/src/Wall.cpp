#include "../include/Wall.h"

Wall::Wall(float x, float y)
{
    position.x = x;
    position.y = y;
    mTransform = new TransformComponent(x, y, GAME_PIXELS, GAME_PIXELS, 1);
    mCollider = new ColliderComponent(mTransform, "Wall");
}

Wall::~Wall()
{
    position.Zero();
    delete mCollider;
    delete mTransform;
}
