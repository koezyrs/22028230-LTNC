#include "Event.h"

Event::Event(float x, float y, std::function<void()> func)
:position(x,y) , EventFunction([this,func] {func();})
{
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

void Event::Perform()
{
    EventFunction();
}
