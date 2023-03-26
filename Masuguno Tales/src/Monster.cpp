#include "Monster.h"

Monster::Monster(float _x, float _y, int _width, int _height, int _scale, const char* filepath, std::string name, int _speed)
: position(_x,_y), speed(_speed)
{
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(filepath, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Monster");
    mName = new NameComponent(mTransform, name, "data files/font/game.ttf", 10, SDL_Color{255,255,255});
    mAI = new AIComponent(mTransform, speed);
}

Monster::~Monster()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
    delete mAI;
}
