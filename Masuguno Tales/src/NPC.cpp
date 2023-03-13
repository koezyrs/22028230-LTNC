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
    if(DialogueManager::dialogueList[npcName].CONTENT.empty())
    {
        std::cout << "Unable to find " << npcName << " conversation!"  << std::endl;
        return;
    }
    DialogueType context = DialogueManager::dialogueList[npcName];
    Game::gDialogue->setTitleLabel(context.TITLE.c_str());
    Game::gDialogue->setContentLabel(context.CONTENT.c_str());
    Game::gDialogue->setOption1(context.REPLY1.c_str(), context.func1);
    Game::gDialogue->setOption2(context.REPLY2.c_str(), context.func2);
    Game::gDialogue->setOption3(context.REPLY3.c_str(), context.func3);
    Game::gDialogue->setOption4(context.REPLY4.c_str(), context.func4);
    Game::gDialogue->showWindow();
}

void NPC::HideDialogue()
{
    Game::gDialogue->hideWindow();
}
