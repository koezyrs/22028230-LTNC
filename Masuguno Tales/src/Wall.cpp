#include "../include/Wall.h"

Wall::Wall()
{
    mTransform = new TransformComponent(300.0f, 300.0f, 300, 20, 1);
    mSprite = new SpriteComponent("assets/dirt.png", mTransform);
    mCollider = new ColliderComponent(mTransform, "Wall");
}

Wall::~Wall()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
}

void Wall::Update()
{
    mTransform->Update();
    mCollider->Update();
    mSprite->Update();
}

void Wall::Render()
{
     mSprite->Render();
}
