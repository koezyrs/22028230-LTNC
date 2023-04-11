#include "Event.h"

Event::Event(float x, float y)
{
    position.x = x;
    position.y = y;
    mTransform = new TransformComponent(x, y, GAME_PIXELS, GAME_PIXELS, 1);
    mCollider = new ColliderComponent(mTransform, "Event");
}

Event::~Event()
{
    delete mTransform;
    delete mCollider;
}

void Event::Update()
{
    mTransform->position.x = position.x;
    mTransform->position.y = position.y;
    mCollider->Update();
}
TransformComponent* Event::getTransformComponent()
{
    return mTransform;
}
ColliderComponent* Event::getColliderComponent()
{
    return mCollider;
}
bool Event::isActive()
{
    return active;
}
void Event::destroy()
{
    active = false;
}
