#pragma once
#ifndef QuestDB_h
#define QuestDB_h

#include <map>
#include "../Game.h"
#include "../Actor.h"
#include "../Quest.h"
#include "../Inventory.h"

class QuestDB
{
public:
    static void LoadQuestDatabase();
    static void giveQuest(int quest_id);
    static void dropQuest(int quest_id);
    static bool checkQuest(int quest_id);
    static std::map<int, Quest> questDatabase;
};

#endif // QuestDB_h
