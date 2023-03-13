#include <iostream>
#include "NPC.h"
#include "Game.h"
#include "DialogueManager.h"
NPC::NPC(float _x, float _y, int _width, int _height, int _scale, const char* filepath, std::string name)
: position(_x,_y), npcName(name)
{
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(filepath, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "NPC");
    mName = new NameComponent(mTransform, name, "data files/font/game.ttf", 10, SDL_Color{255,255,255});
}

NPC::~NPC()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
}

void NPC::PlayDialogue()
{
    DialogueManager::Play(npcName);
}

void NPC::HideDialogue()
{
    Game::gDialogue->hideWindow();
}
