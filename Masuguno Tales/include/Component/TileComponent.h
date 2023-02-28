#pragma once
#ifndef TileComponent_h
#define TileComponent_h

#include <SDL.h>
#include <string>
#include "TransformComponent.h"
#include "SpriteComponent.h"

class TileComponent
{
public:
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    SDL_Rect tileRect;
    int tileID;
    std::string path;

    TileComponent();
    TileComponent(int _x, int _y, int _w, int _h, int _id)
    {
        tileRect.x = _x;
        tileRect.y = _y;
        tileRect.w = _w;
        tileRect.h = _h;
        tileID = _id;

        switch(tileID)
        {
            case 0:
                path = "assets/water.png";
                break;
            case 1:
                path = "assets/dirt.png";
                break;
            case 2:
                path = "assets/grass.png";
                break;
            default:
                break;
        }
        mTransform = new TransformComponent((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
        mSprite = new SpriteComponent(path.c_str(), mTransform);
    }

};

#endif // TileComponent_h
