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
    dialogueList["Guild Master#6"] = DialogueType("Conversation with Aurez",
                                             "You are very brave adventurer! The prize you will get what you are deserved!",
                                             "1. That seems challenging, but nothing can stop me. I'm in sir!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");

    dialogueList["Guild Master#5"] = DialogueType("Conversation with Aurez",
                                             "Excellent work on your training. Now it's time to put your skills to the test. We have a problem with some blue slimes that have been attacking travelers on the road. We need you to hunt down and defeat 5 of them. Bring back their phlegm as proof of your success.",
                                             "1. That seems challenging, but nothing can stop me. I'm in sir!",
                                             "2. This quest is too hard for me, I will get stronger and come back later!",
                                             NULL,
                                             NULL,
                                             []{
                                                 QuestLog::giveQuest(2);
                                                 Play("Guild Master#6");
                                                },
                                             []{
                                                    Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#4"] = DialogueType("Conversation with Aurez",
                                             "You haven't defeat 10 dummies yet! Train harder adventurer!",
                                             "1. Oh, my bad. I will get back training!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#3"] = DialogueType("Conversation with Aurez",
                                             "Nice, come back to see me when you finish!",
                                             "1. Got it sir!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#2"] = DialogueType("Conversation with Aurez",
                                             " Ah, yes. Leiea is one of our most experienced adventurers. It's good to see she's helping out new arrivals. I'm the guild master, and I have plenty of tasks that need doing. But first, we need to see what you're capable of. Your quest is to hone your combat abilities by attacking 10 practice dummies.",
                                             "1. I'm ready, let's do it!",
                                             "2. I think I'm gonna take a look around a bit!",
                                             NULL,
                                             NULL,
                                             []{
                                                  QuestLog::giveQuest(1);
                                                  Play("Guild Master#3");
                                                },
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#1"] = DialogueType("Conversation with Aurez",
                                             "Hello adventurer! I'm Aurez - the guild master. What can I help you today!",
                                             "1. Hello, I was told to come see you by a green-haired adventurer named Leiea. She said you could help me get started with some quests.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Guild Master#2");
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");

    dialogueList["Leiea: Introduce#3"] = DialogueType("Conversation with Leiea",
                                             "Great! It's not far from here. Just head straight down this path until you reach the town gates. Once you're inside, the guild hall is on the left side of the main square. Just tell the guild master that Leiea sent you and he'll give you all the details. Good luck adventurer!",
                                             "1. Thank you so much, Leiea. I'll make sure to do my best on this quest.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Leiea");
    dialogueList["Leiea: Introduce#2"] = DialogueType("Conversation with Leiea",
                                             " I'm glad you think so! There's so much to see and do here. The guild master in the nearby town is looking for adventurers to help with a quest. Would you be interested?",
                                             "1. Absolutely! I've always wanted to go on a real adventure.",
                                             "2. No I think I'm good.",
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Leiea: Introduce#3");
                                                },
                                             []{
                                                Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             "Face-Leiea");

    dialogueList["Leiea: Introduce#1"] = DialogueType("Conversation with Leiea",
                                             "You're in Masuguno Land! This is a fantasy world , there are magic, and all sorts of creatures here. My name is Leiea!",
                                             "1. Hi Leiea!. I can't believe I'm in a fantasy world... this is incredible!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Leiea: Introduce#2");
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Leiea");

    dialogueList["Leiea Lv. 6"] = DialogueType("Conversation with Leiea",
                                             "Hello there! Are you lost?",
                                             "1. Yes, I think I am. I'm not from around here. What is this place?",
                                             "2. No, I think I know where I'm going!",
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Leiea: Introduce#1");
                                                },
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                 },
                                             []{},
                                             []{},
                                             "Face-Leiea");
}

