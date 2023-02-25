#pragma once

#ifndef TransformComponent_h
#define TransformComponent_h

#include "../Vector2D.h"

class TransformComponent
{
public:
    Vector2D position;
    Vector2D velocity;
    int speed = 5;

    TransformComponent()
    {
        position.x = 0.0f;
        position.y = 0.0f;
        velocity.x = 0;
        velocity.y = 0;
    }

    TransformComponent(float _x, float _y)
    {
        position.x = _x;
        position.y = _y;
    }
    void Update()
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

#endif // TransformComponent_h
