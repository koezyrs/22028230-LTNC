#include "Projectile.h"

#include "TextureManager.h"
Projectile::Projectile(float _x, float _y ,int _frames, int _speed, std::string _tag, std::string skillSprite, float _damage)
: active(true), position(_x,_y) , frames(_frames), speed(_speed), tag(_tag), damage(_damage)
{
    mTransform = new TransformComponent(_x, _y, 64, 64, 1);
    mCollider = new ColliderComponent(mTransform, "Projectile");
    mTexture = TextureManager::GetTexture(skillSprite);
    SDL_QueryTexture(mTexture, NULL, NULL, &Width, &Height);
    srcRect = {0,0,192,192};
    destRect = {0,0,0,0};
    startTime = SDL_GetTicks();
}

Projectile::~Projectile()
{
    delete mTransform;
    delete mCollider;
    mTexture = NULL;
}
