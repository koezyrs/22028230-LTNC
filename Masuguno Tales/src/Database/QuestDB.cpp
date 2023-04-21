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
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        1,                                  // Enemy id
        1,                                  // Enemy amount
        // Reward
        10,                                 // Exp
        1,                                  // Gold
        1,                                  // Reward item id
        5,                                  // Reward item amount
        1,                                  // Reward equip id
        0,                                  // Reward equip amount
        true                               // Repeat
    );

}
