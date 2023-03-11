#pragma once
#ifndef AIComponent_h
#define AIComponent_h

#include <cstdlib>
#include "Component.h"

class AIComponent
{
public:
    AIComponent(TransformComponent* trans)
    {
        mTransform = trans;
        mTransform->speed = 1;
    }
    ~AIComponent();
    void Update()
    {
//        srand(time(0));
    }
private:
    TransformComponent* mTransform;
};
#endif // AIComponent_h
