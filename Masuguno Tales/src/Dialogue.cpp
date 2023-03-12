#include "Dialogue.h"

Dialogue::Dialogue(int _x, int _y, int _width, int _height, const char* title, const char* facefile, const char* content)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)

{
    DialogueBox = TextureManager::LoadTexture("data files/graphics/gui/Dialogue.png");
    Face = TextureManager::LoadTexture(facefile); // (x,y) = (24,40)
    closeButton = new Button("data files/graphics/gui/8.png", "data files/graphics/gui/9.png", _x + 461, _y + 5, 13, 13, [this]{Window::Toggle(); });
    dialogueTitle = new Label("data files/font/game.ttf", title, 10, _x + 5, _y + 5, SDL_Color{255,255,255}, false, []{});
    dialogueContent = new Label("data files/font/game.ttf", content, 10, _x + 134, _y + 45, SDL_Color{255,255,255}, 320, false, []{});
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};
    faceSrcRect ={0, 0, 96, 96};
    faceDestRect ={_x + 24, _y + 40, 96, 96};
}

Dialogue::~Dialogue()
{
    delete closeButton;
    delete dialogueTitle;
    delete dialogueContent;
    SDL_DestroyTexture(DialogueBox);
    SDL_DestroyTexture(Face);
    Face = NULL;
    DialogueBox = NULL;
}
