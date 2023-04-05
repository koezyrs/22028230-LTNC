#include "Monster.h"

Monster::Monster(float _x, float _y, int _width, int _height, int _scale,  std::string _monsterName,
                 std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                 float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed)
: startPosition(_x,_y), monsterName(_monsterName), monsterSprite(_monsterSprite), damage(_damage), health(_health),
    attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed), roamSpeed(_roamSpeed), attackRange(_attackRange),
    stopChaseRange(_stopChaseRange)
{
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(monsterSprite, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Monster");
    mName = new NameComponent(mTransform, monsterName, "data files/font/game.ttf", 10, SDL_Color{255,255,255});
    mAI = new AIComponent(mTransform, startPosition, damage, attackSpeed, attackRange, stopChaseRange, chaseSpeed, roamSpeed, &trigger);
}

Monster::~Monster()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
    delete mAI;
}
