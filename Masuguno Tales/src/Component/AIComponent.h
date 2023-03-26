#pragma once
#ifndef AIComponent_h
#define AIComponent_h

#include "Component.h"
#include "../EventManager.h"

class AIComponent
{
public:
    AIComponent(TransformComponent* trans, float _speed)
    :speed(_speed)
    {
        mTransform = trans;
    }
    ~AIComponent() {}
    void Update()
    {
        int coordinateX = (static_cast<int>(mTransform->position.x)) / GAME_PIXELS;
        int coordinateY = (static_cast<int>(mTransform->position.y)) / GAME_PIXELS;
        float x = speed * static_cast<float>(EventManager::getMapTiles()[coordinateY][coordinateX].flowDirectionX);
        float y = speed * static_cast<float>(EventManager::getMapTiles()[coordinateY][coordinateX].flowDirectionY);
        std::cout << x << " " << y << std::endl;
        mTransform->position.Add(Vector2D(x,y));
    }

private:
    TransformComponent* mTransform;
    float speed;
};

#endif // AIComponent_h
