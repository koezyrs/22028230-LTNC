#include "Dialogue.h"

Dialogue::Dialogue(int _x, int _y, int _width, int _height, const char* title)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)

{
    DialogueBox = TextureManager::LoadTexture("data files/graphics/gui/Dialogue.png");
    closeButton = new Button("data files/graphics/gui/8.png", "data files/graphics/gui/9.png", _x + 461, _y + 5, 13, 13, [this]{Window::hideWindow(); });
    dialogueTitle = new Label("data files/font/game.ttf", title, 10, _x + 5, _y + 5, SDL_Color{255,255,255});
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};
}

Dialogue::~Dialogue()
{
    delete closeButton;
    delete dialogueTitle;
    SDL_DestroyTexture(DialogueBox);
    DialogueBox = NULL;
}
