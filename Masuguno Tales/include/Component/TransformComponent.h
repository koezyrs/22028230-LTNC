#pragma once

#ifndef TransformComponent_h
#define TransformComponent_h

#include "../Vector2D.h"
#include "../Config.h"
#include "Component.h"

class TransformComponent
{
public:
    Vector2D position;
    Vector2D velocity;
    int width = GAME_PIXELS;
    int height = GAME_PIXELS;
    int scale = 1;
    int speed = 2;

    TransformComponent()
    {
        position.Zero();
        velocity.Zero();
    }

    TransformComponent(int _scale)
    {
        position.Zero();
        velocity.Zero();
        scale = _scale;
    }

    TransformComponent(float _x, float _y)
    {
        position.x = _x;
        position.y = _y;
        velocity.Zero();
    }

    TransformComponent(float _x, float _y, int _width, int _height, int _scale)
    {
        position.x = _x;
        position.y = _y;
        width = _width;
        height = _height;
        scale = _scale;
        velocity.Zero();
    }

    ~TransformComponent()
    {
        position.Zero();
        velocity.Zero();
        width = height = scale = speed = 0;
    }
    void Update()
    {
        position.x += velocity.x;
        position.y += velocity.y;
    }
};

#endif // TransformComponent_h
