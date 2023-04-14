#include "InputBox.h"

InputBox::InputBox(float x, float y, int width, int height, int characterLimit)
: position(x,y), Width(width), Height(height), CharacterLimit(characterLimit)
{
    SDL_StopTextInput();
    inputText = new Label(GAME_FONT, " ", 10, x, y, White, characterLimit*10, false, []{});
    inputValue = "";
}

InputBox::~InputBox()
{
    delete inputText;
}

void InputBox::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // check if the mouse is in the button
        if((x < position.x) || (x > position.x + Width) || (y < position.y) || (y > position.y + Height)) inside = false;
        else inside = true;

        if(inside && e->type == SDL_MOUSEBUTTONDOWN) {active = true; SDL_StartTextInput();}

        if (!inside && e->type == SDL_MOUSEBUTTONDOWN) {active = false; SDL_StopTextInput();}
    }

    if(active)
    {
        switch(e->type)
        {
        case SDL_TEXTINPUT:
            inputValue += e->text.text;
            inputText->Reset();
            inputText = new Label(GAME_FONT, inputValue.c_str(), 10, position.x, position.y, White, CharacterLimit * 10, false, []{});
            break;
        case SDL_KEYDOWN:
            if(e->key.keysym.sym == SDLK_BACKSPACE)
            {
                int n = inputValue.length();
                if(n <= 0) break;
                inputValue.erase(n - 1);
                inputText->Reset();
                inputText = new Label(GAME_FONT, inputValue.c_str(), 10, position.x, position.y, White, CharacterLimit * 10, false, []{});
                break;
            }
            break;
        }
    }
}

void InputBox::Render()
{
    inputText->Render();
}
