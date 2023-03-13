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
    std::string REPLY1;
    std::string REPLY2;
    std::string REPLY3;
    std::string REPLY4;
    std::function<void()> func1;
    std::function<void()> func2;
    std::function<void()> func3;
    std::function<void()> func4;

    DialogueType(std::string title = "", std::string content = "", std::string reply1 = "", std::string reply2 = "",
                 std::string reply3 = "", std::string reply4 = "",
                 std::function<void()> funct1 = []{}, std::function<void()> funct2 = []{},
                 std::function<void()> funct3 = []{}, std::function<void()> funct4 = []{})
    : TITLE(title), CONTENT(content), REPLY1(reply1), REPLY2(reply2), REPLY3(reply3), REPLY4(reply3),
        func1([this, funct1] {funct1();}), func2([this, funct2] {funct2();}), func3([this, funct3] {funct3();}), func4([this, funct4] {funct4();})
    {}
};

class DialogueManager
{
public:
    static void LoadDialogue();
    static std::map<std::string, DialogueType> dialogueList;
};

#endif // DialogueManager_h
