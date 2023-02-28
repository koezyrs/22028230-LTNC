#include <string>
#include "../include/Map.h"
#include "../include/TextureManager.h"

Map::Map(int x, int y, int w, int h, int id, std::string _tag)
{
    mTile = new TileComponent(x, y, w, h, id);
    mCollider = new ColliderComponent(mTile->mTransform, _tag);

};

Map::~Map()
{
    delete mTile;
    delete mCollider;
};

void Map::Update()
{
    mTile->mTransform->Update();
    mCollider->Update();
    mTile->mSprite->Update();
}

void Map::Render()
{
    mTile->mSprite->Render();
}


