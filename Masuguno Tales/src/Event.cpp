#include <iostream>
#include "Event.h"
#include "EventManager.h"
#include "Settings.h"
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
