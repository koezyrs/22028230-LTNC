#include "NPC.h"
NPC::NPC(float _x, float _y, int _width, int _height, int _scale, const char* filepath, std::string name)
{
    position.x = _x;
    position.y = _y;
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(filepath, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "NPC");
    mName = new NameComponent(mTransform, name, "data files/font/game.ttf", 10, SDL_Color{255,255,255});

    TestNPCDialogue = new Dialogue(static_cast<int> ((SCREEN_WIDTH - 478)/2), static_cast<int> ((SCREEN_HEIGHT - 226)/2), 478, 226, "Test Dialogue", "data files/graphics/faces/18.png",
                        "Welcome Adventure, this is the Masuguno Tales World! I'm very happy to have you here! But you are look like you don't know who you are and where you at!");
}

NPC::~NPC()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
    delete TestNPCDialogue;
}

void NPC::PlayDialogue()
{
    TestNPCDialogue->showWindow();
}

void NPC::HideDialogue()
{
    TestNPCDialogue->hideWindow();
}
