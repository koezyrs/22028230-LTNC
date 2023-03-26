#pragma once
#ifndef DialogueManager_h
#define DialogueManager_h

#include <map>
#include <string>
#include <vector>
#include <functional>

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

class DialogueManager
{
public:
    static void Play(std::string dialogueName);
    static void LoadDialogue();
    static std::map<std::string, DialogueType> dialogueList;
};

#endif // DialogueManager_h
