#include "Actor.h"
#include "TextureManager.h"

Actor::Actor(float x, float y, const char* filetex) : Entity::Entity()
{
    mTransform = new TransformComponent(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, GAME_SCALE);
    mSprite = new SpriteComponent(filetex, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite);
    mName = new NameComponent(mTransform, "Tuan Duong Lv.99" , "data files/font/game.ttf", 10, SDL_Color{0,0,0});
}

Actor::~Actor()
{
    delete mController;
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
}
