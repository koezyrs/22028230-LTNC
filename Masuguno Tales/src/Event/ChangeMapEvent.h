#pragma once
#ifndef ChangeMapEvent_h
#include "../Event.h"
#include "../EventManager.h"

class ChangeMapEvent : public Event
{
private:
    int mapID = 1;
public:
    ChangeMapEvent(float x, float y, int ID) : Event::Event(x, y)
    {
        mapID = ID;
    }
    virtual ~ChangeMapEvent() {}
    void Perform() override
    {
        EventManager::ChangeMap(mapID);
    }
};

#endif // ChangeMapEvent_h

