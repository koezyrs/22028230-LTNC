#include <string>
#include "Game.h"
#include "Actor.h"
#include "Dialogue.h"
#include "DialogueManager.h"
#include "Inventory.h"

std::map<std::string, DialogueType> DialogueManager::dialogueList;

void DialogueManager::Play(std::string dialogueName)
{
    if(DialogueManager::dialogueList[dialogueName].CONTENT.empty())
    {
        std::cout << "Unable to find " << dialogueName << " conversation!"  << std::endl;
        return;
    }
    DialogueType context = DialogueManager::dialogueList[dialogueName];
    Game::gDialogue->setFace(context.FACEPATH.c_str());
    Game::gDialogue->setTitleLabel(context.TITLE.c_str());
    Game::gDialogue->setContentLabel(context.CONTENT.c_str());
    Game::gDialogue->setOption1(context.REPLY1, context.FUNC1);
    Game::gDialogue->setOption2(context.REPLY2, context.FUNC2);
    Game::gDialogue->setOption3(context.REPLY3, context.FUNC3);
    Game::gDialogue->setOption4(context.REPLY4, context.FUNC4);
    Game::gDialogue->showWindow();
}

void DialogueManager::LoadDialogue()
{
    dialogueList["The Guard Introduction"] = DialogueType("Conversation with the Guard",
                                             "You at no where to be found hahaah!",
                                             "1. Shit",
                                             "2. Decrease Mana (-10MP)",
                                             "3. Regen Mana (+10MP)",
                                             NULL,
                                             []{Game::gDialogue->hideWindow();},
                                             []{Game::gPlayer->mStats->Mana -= 10;},
                                             []{Game::gPlayer->mStats->Mana += 10;},
                                             []{},
                                             "Face-Guard1");


    dialogueList["The Guard"] = DialogueType("Conversation with the Guard",
                                             "Bipbom",
                                             "1. Where Am I?",
                                             "2. I don't care!",
                                             "3. Attack me (-10 HP)",
                                             "4. Heal me (+10 HP)",
                                             []{DialogueManager::Play("The Guard Introduction");},
                                             []{Game::gDialogue->hideWindow();},
                                             []{Game::gPlayer->mStats->Health -= 10;},
                                             []{Game::gPlayer->mStats->Health += 10;},
                                             "Face-Guard1");
}

