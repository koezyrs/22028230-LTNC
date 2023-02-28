#pragma once

#ifndef Map_h
#define Map_h
#include "Game.h"
#include "Component/Component.h"

class Map
{
public:
    Map(int x, int y, int w, int h, int id, std::string tag);
    void Update();
    void Render();
    ~Map();
private:
    TileComponent* mTile;
    ColliderComponent* mCollider;

};

#endif // Map_h
