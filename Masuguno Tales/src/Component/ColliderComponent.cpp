#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(TransformComponent* trans)
{
    mTransform = trans;
    tag = "";
}

ColliderComponent::ColliderComponent(TransformComponent* trans, std::string _tag)
{
    mTransform = trans;
    tag = _tag;
}

void ColliderComponent::Update()
{
    mCollider.x = static_cast<int>(mTransform->position.x) - Game::gCamera.x;
    mCollider.y = static_cast<int>(mTransform->position.y) - Game::gCamera.y;
    mCollider.w = mTransform->width * mTransform->scale;
    mCollider.h = mTransform->height * mTransform->scale;
}
