#pragma once
#ifndef TileComponent_h
#define TileComponent_h

#include <SDL.h>
#include <string>
#include "../Vector2D.h"
#include "Component.h"

class TileComponent
{
private:
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
    Vector2D position;
    int tileID;
    std::string tag;
public:
    TileComponent();
    TileComponent(int _x, int _y, int _w, int _h, int _id)
    {
        tileID = _id;
        position.x = static_cast<float> (_x);
        position.y = static_cast<float> (_y);
        switch(tileID)
        {
            case 0:
                tag = "Block";
                break;
            case 1:
                tag = "Allow";
                break;
            default:
                tag = "Allow";
                break;
        }

        mTransform = new TransformComponent(position.x, position.y, _w, _h, 1);
        mCollider = new ColliderComponent(mTransform, tag);
    }

    ~TileComponent()
    {
        delete mTransform;
        delete mCollider;
    }

    void Update()
    {
        mTransform->position.x = position.x - Game::gCamera.x;
        mTransform->position.y = position.y - Game::gCamera.y;

        mCollider->Update();
    }

    void Render(){}

};

#endif // TileComponent_h
