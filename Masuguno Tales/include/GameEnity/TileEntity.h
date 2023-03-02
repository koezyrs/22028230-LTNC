#pragma once
#ifndef TileEntity_h
#define TileEntity_h

#include <string>
#include "../Game.h"
#include "../Entity.h"
#include "../Component/Component.h"
#include "../config.h"

class TileEntity : public Entity
{
public:
    TileEntity(int id, int x, int y, std::string tag);
    ~TileEntity();
    void Update() override
    {
        mTile->mTransform->Update();
        mColider->Update();
        mTile->mSprite->Update();
    }
    void Render() override
    {
        mTile->mSprite->Render();
    }
private:
    TileComponent* mTile;
    ColliderComponent* mColider;
};

TileEntity::TileEntity(int id, int x, int y, std::string tag) : Entity::Entity()
{
    mTile = new TileComponent(x, y, GAME_PIXELS, GAME_PIXELS, id);
    mColider = new ColliderComponent(mTile->mTransform, tag);
    Game::gGroupMap.push_back(this);
}

TileEntity::~TileEntity() {}
#endif // TileEntity_h


