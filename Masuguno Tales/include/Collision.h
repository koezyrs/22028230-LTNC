#pragma once
#ifndef Collision_h
#define Collision_h

#include <SDL.h>

class Collision
{
public:
    static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB); // Access Aligned Bounding Box
};
#endif // Collision_h
