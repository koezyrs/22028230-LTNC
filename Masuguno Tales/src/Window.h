#pragma once
#ifndef Window_h
#define Window_h

#include "Component/Component.h"

class Window
{
public:
    Window();
    virtual ~Window();
    bool isActive() {return active;}
    bool isHide() {return hide;}
    void destroy() {active = false;}
    void showWindow() {hide = false;}
    void hideWindow() {hide = true;}
    virtual void Update() = 0;
    virtual void Render() = 0;
private:
    bool hide = false;
    bool active = true;
};

#endif // Window_h
