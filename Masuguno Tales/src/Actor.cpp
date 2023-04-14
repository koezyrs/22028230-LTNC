#include "Actor.h"

Actor::Actor(float x, float y, std::string spriteName) : Entity::Entity()
{
    mTransform = new TransformComponent(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, GAME_SCALE);
    mSprite = new SpriteComponent(spriteName, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite);
    mName = new NameComponent(mTransform, "Tuan Duong" , "data files/font/game.ttf", 10, SDL_Color{0,0,0});
    mStats = new StatsComponent(1,0,100,5,2,10,20,5,0,10);
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

void Actor::Update()
{
    mController->Update();
    mTransform->Update();
    mCollider->Update();
    mStats->Update();
    mSprite->Update();
    mName->Update();
}
void Actor::Render()
{
    mSprite->Render();
    mName->Render();
}
TransformComponent* Actor::getTransformComponent()
{
    return mTransform;
}
ColliderComponent* Actor::getColliderComponent() {
    return mCollider;
}
KeyboardController* Actor::getKeyboardController() {
    return mController;
}
SpriteComponent* Actor::getSpriteComponent() {
    return mSprite;
}
NameComponent* Actor::getNameComponent() {
    return mName;
}

bool Actor::isActive() const{
    return active;
}
void Actor::destroy() {
    active = false;
}

void Actor::setPosition(float x, float y)
{
    mTransform->position = Vector2D(x,y);
}
