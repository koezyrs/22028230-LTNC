#pragma once
#ifndef EventManager_h
#define EventManager_h

class EventManager
{
public:
    static void ChangeMap(int xpos, int ypos, float actorXPos, float actorYPos, const char* maptex, const char* mapfile, int sizeX, int sizeY);
};
#endif // EventManager_h
