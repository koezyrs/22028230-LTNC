#include "../include/Monster.h"

Monster::Monster(float _x, float _y, int _width, int _height, int _scale, const char* filepath)
{
    position.x = _x;
    position.y = _y;
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(filepath, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Monster");
}

Monster::~Monster()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
}
