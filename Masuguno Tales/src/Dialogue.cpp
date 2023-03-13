#include "Dialogue.h"

Dialogue::Dialogue(int _x, int _y, int _width, int _height, const char* title, const char* facefile, const char* content)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)

{
    DialogueBox = TextureManager::LoadTexture("data files/graphics/gui/Dialogue.png");
    Face = TextureManager::LoadTexture(facefile); // (x,y) = (24,40)
    closeButton = new Button("data files/graphics/gui/8.png", "data files/graphics/gui/9.png", _x + 461, _y + 5, 13, 13, [this]{Window::Toggle(); });
    dialogueTitle = new Label("data files/font/game.ttf", title, 10, _x + 5, _y + 5, SDL_Color{255,255,255}, false, []{});
    dialogueContent = new Label("data files/font/game.ttf", content, 10, _x + 134, _y + 45, SDL_Color{255,255,255}, 320, false, []{});
    dialogueOption1 = new Label("data files/font/game.ttf", "1.", 10, _x + 25, _y + 145, SDL_Color{0,0,0}, 430, false, []{});
    dialogueOption2 = new Label("data files/font/game.ttf", "2.", 10, _x + 25, _y + 160, SDL_Color{0,0,0}, 430, false, []{});
    dialogueOption3 = new Label("data files/font/game.ttf", "3.", 10, _x + 25, _y + 175, SDL_Color{0,0,0}, 430, false, []{});
    dialogueOption4 = new Label("data files/font/game.ttf", "4.", 10, _x + 25, _y + 190, SDL_Color{0,0,0}, 430, false, []{});
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
    delete dialogueOption1;
    delete dialogueOption2;
    delete dialogueOption3;
    delete dialogueOption4;
    SDL_DestroyTexture(DialogueBox);
    SDL_DestroyTexture(Face);
    Face = NULL;
    DialogueBox = NULL;
}

void Dialogue::setFace(const char* facePath)
{
    SDL_DestroyTexture(Face);
    Face = NULL;
    Face = TextureManager::LoadTexture(facePath);
}

void Dialogue::setTitleLabel(const char* title)
{
    dialogueTitle->Reset();
    dialogueTitle = new Label("data files/font/game.ttf", title, 10, position.x + 5, position.y + 5, SDL_Color{255,255,255}, false, []{});
}

void Dialogue::setContentLabel(const char* content)
{
    dialogueContent->Reset();
    dialogueContent = new Label("data files/font/game.ttf", content, 10, position.x + 134, position.y + 45, SDL_Color{255,255,255}, 320, false, []{});

}

void Dialogue::setOption1(const char* text, std::function<void()> func)
{
    dialogueOption1->Reset();
    if(text != "") dialogueOption1 = new Label("data files/font/game.ttf", text, 10, position.x + 25, position.y + 145, SDL_Color{0,0,0}, 430, true, func);
}

void Dialogue::setOption2(const char* text, std::function<void()> func)
{
    dialogueOption2->Reset();
    if(text != "") dialogueOption2 = new Label("data files/font/game.ttf", text, 10, position.x + 25, position.y + 160, SDL_Color{0,0,0}, 430, true, func);
}

void Dialogue::setOption3(const char* text, std::function<void()> func)
{
    dialogueOption3->Reset();
    if(text != "") dialogueOption3 = new Label("data files/font/game.ttf", text, 10, position.x + 25, position.y + 175, SDL_Color{0,0,0}, 430, true, func);
}

void Dialogue::setOption4(const char* text, std::function<void()> func)
{
    dialogueOption4->Reset();
    if(text != "") dialogueOption4 = new Label("data files/font/game.ttf", text, 10, position.x + 25, position.y + 190, SDL_Color{0,0,0}, 430, true, func);
}
