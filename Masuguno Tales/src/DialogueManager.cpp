#include "DialogueManager.h"

struct DialogueType
{
    std::string TITLE;
    std::string CONTENT;
    const char* REPLY1;
    const char* REPLY2;
    const char* REPLY3;
    const char* REPLY4;
    std::function<void()> FUNC1;
    std::function<void()> FUNC2;
    std::function<void()> FUNC3;
    std::function<void()> FUNC4;
    std::string FACEPATH;

    DialogueType(std::string title = "", std::string content = "", const char* reply1 = NULL, const char* reply2 = NULL,
                 const char* reply3 = NULL, const char* reply4 = NULL,
                 std::function<void()> funct1 = []{}, std::function<void()> funct2 = []{},
                 std::function<void()> funct3 = []{}, std::function<void()> funct4 = []{}, std::string facePath = "")
    : TITLE(title), CONTENT(content), REPLY1(reply1), REPLY2(reply2), REPLY3(reply3), REPLY4(reply4),
        FUNC1([this, funct1] {funct1();}), FUNC2([this, funct2] {funct2();}), FUNC3([this, funct3] {funct3();}), FUNC4([this, funct4] {funct4();}) , FACEPATH(facePath)
    {}
};
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

