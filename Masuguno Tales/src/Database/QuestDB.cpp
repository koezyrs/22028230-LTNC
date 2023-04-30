#include "QuestDB.h"

std::map<int, Quest> QuestDB::questDatabase;

void QuestDB::LoadQuestDatabase()
{
    questDatabase[1] = Quest(
        // Requirements
        1,                                  // Quest id (Must match database)
        "Train with the dummies",           // Quest name
        "The dummies can be find at the gate of town! Defeat 10 of those!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        3,                                  // Enemy id
        10,                                  // Enemy amount
        // Reward
        30,                                 // Exp
        10,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );

}
