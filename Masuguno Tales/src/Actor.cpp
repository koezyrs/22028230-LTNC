#include "Actor.h"
#include "TextureManager.h"

Actor::Actor(float x, float y, const char* filetex) : Entity::Entity()
{
    mTransform = new TransformComponent(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, GAME_SCALE);
    mSprite = new SpriteComponent(filetex, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite);
    mName = new NameComponent(mTransform, "Tuan Duong" , "data files/font/game.ttf", 10, SDL_Color{0,0,0});
    mStats = new StatsComponent(1,0,100,100,100,30,30,3,5,1);
}

Actor::~Actor()
{
    delete mController;
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
    delete mStats;
}
