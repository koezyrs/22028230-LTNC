#include "QuestDB.h"

std::map<int, Quest> QuestDB::questDatabase;

void QuestDB::LoadQuestDatabase()
{
    questDatabase[1] = Quest(
        // Requirements
        1,                                  // Quest id (Must match database)
        "Beginner Quest",                   // Quest name
        "Hi this is your first quest!",     // Desc
        0,                                  // Var id
        0,                                  // Var amount
        1,                                  // Item id
        5,                                  // Item amount
        1,                                  // Equip id
        1,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        10,                                 // Exp
        1,                                  // Gold
        1,                                  // Reward item id
        5,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );

}
