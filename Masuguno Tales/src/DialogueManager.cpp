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

    dialogueList["The Guard"] = DialogueType("Conversation with the Guard",
                                             "Kill 10 cow!",
                                             "1. Ok let me do the quest",
                                             "2. I don't care!",
                                             "3. I've done the quest!",
                                             "4. I want to buy",
                                             []{
                                                 if(QuestLog::giveQuest(1)) Play("The Guard Introduction");
                                                 else Play("Failed to give quest");
                                                },
                                             []{
                                                 Game::gShop->OpenShop(2);
                                                 },
                                             []{
                                                 if(QuestLog::checkQuest(1)) Play("Good Job");
                                                    else Play("Finish the quest bro");
                                                 },
                                             []{
                                                 Game::gShop->OpenShop(1);
                                                },
                                             "Face-Guard1");

    dialogueList["Failed to give quest"] = DialogueType("Conversation with the Guard",
                                             "You have received this quest before!",
                                             "1. Ok that's fine",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{Game::gDialogue->hideWindow();},
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Guard1");

    dialogueList["The Guard Introduction"] = DialogueType("Conversation with the Guard",
                                             "Good luck at your quest",
                                             "1. Thanks I will do my best",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{Game::gDialogue->hideWindow();},
                                             []{Game::gDialogue->hideWindow();},
                                             []{Game::gDialogue->hideWindow();},
                                             []{Game::gDialogue->hideWindow();},
                                             "Face-Guard1");

    dialogueList["Good Job"] = DialogueType("Conversation with the Guard",
                                             "Nice this is some reward for you!",
                                             "1. Thanks",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{Game::gDialogue->hideWindow();},
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Guard1");
    dialogueList["Finish the quest bro"] = DialogueType("Conversation with the Guard",
                                             "You haven't finished the quest!",
                                             "1. Ok let's me do it!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{Game::gDialogue->hideWindow();},
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Guard1");
}

