#include "Projectile.h"

#include "TextureManager.h"
Projectile::Projectile(float _x, float _y ,int _frames, int _speed, std::string _tag): active(true), position(_x,_y) , frames(_frames), speed(_speed), tag(_tag)
{
    mTransform = new TransformComponent(_x, _y, 960, 192, 1);
    mCollider = new ColliderComponent(mTransform, "Projectile");
    mTexture = TextureManager::GetTexture("Projectile-Attack");
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
