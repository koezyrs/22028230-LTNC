#pragma once

#ifndef TransformComponent_h
#define TransformComponent_h

#include "../Vector2D.h"
#include "../config.h"

class TransformComponent
{
public:
    Vector2D position;
    Vector2D velocity;
    int width = GAME_PIXELS;
    int height = GAME_PIXELS;
    int scale = 1;
    int speed = 5;

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

    void Update()
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

#endif // TransformComponent_h
