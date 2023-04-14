#pragma once
#ifndef InputBox_h
#define InputBox_h

#include <SDL.h>
#include <string>
#include "Label.h"
#include "Vector2D.h"

class InputBox
{
public:
    InputBox(float x, float y, int width, int height, int characterLimit);
    ~InputBox();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void Render();
private:
    SDL_Color White = {255,255,255};
    bool active = false;
    bool inside = false;
    Vector2D position;
    int Width, Height, CharacterLimit;
    Label* inputText;
    std::string inputValue;
};

#endif // InputBox_h
