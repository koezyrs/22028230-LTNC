#include "Game.h"
#include "Dialogue.h"
#include "DialogueManager.h"

std::map<std::string, DialogueType> DialogueManager::dialogueList;

void DialogueManager::LoadDialogue()
{
    dialogueList["The Guard"] = DialogueType("Conversation with the Guard",
                                             "Bipbom",
                                             "1. Where Am I?",
                                             "2. Hi", "", "",
                                             []{Game::gDialogue->hideWindow();},
                                             []{Game::gDialogue->hideWindow();});
}
