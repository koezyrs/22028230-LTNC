#include "Monster.h"
#include "TextureManager.h"

Monster::Monster(float _x, float _y, int _width, int _height, int _scale,  std::string _monsterName,
                 std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                 float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed)
: startPosition(_x,_y), monsterName(_monsterName), monsterSprite(_monsterSprite), damage(_damage), health(_health), maxhealth(_health),
    attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed), roamSpeed(_roamSpeed), attackRange(_attackRange),
    stopChaseRange(_stopChaseRange)
{
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(monsterSprite, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Monster");
    mName = new NameComponent(mTransform, monsterName, "data files/font/game.ttf", 10, SDL_Color{255,255,255});
    mAI = new AIComponent(mTransform, startPosition, damage, attackSpeed, attackRange, stopChaseRange, chaseSpeed, roamSpeed, &trigger);

    // HP Bar
    HPBarTexture = TextureManager::GetTexture("HPBar");
    hpSourceRectBack = {0,0,32,4};
    hpDestRectBack = {static_cast<int>(_x), static_cast<int>(_y) + 37, 32,4};
    hpSourceRectOver = {0,12,32,4};
    hpDestRectOver = {static_cast<int>(_x), static_cast<int>(_y) + 37, 32,4};

    // Targeted Texture
    targetedTexture = TextureManager::GetTexture("Target");
    targetedSrcRect = {0,0,28,28};
    targetedDestRect = {static_cast<int>(_x) + 28, static_cast<int>(_y) - 3, 28,28};
}

void Monster::ApplyDamage(float _damage)
{
    float LO = 0.5f;
    float HI = 1.5f;
    float D = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    int healthLose = _damage * D;

    if(healthLose <= 0) return;
    if(health - healthLose <= 0) health = 0;
    else health -= healthLose;
}

Monster::~Monster()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
    delete mAI;
}
