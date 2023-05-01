#include "QuestDB.h"

std::map<int, Quest> QuestDB::questDatabase;

void QuestDB::LoadQuestDatabase()
{
    questDatabase[5] = Quest(
        // Requirements
        5,                                  // Quest id (Must match database)
        "Defeat 10 green slime",    // Quest name
        "Go to the east of the town, you will see some green slime!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        2,                                  // Enemy id
        10,                                  // Enemy amount
        // Reward
        150,                                 // Exp
        35,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        9,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[4] = Quest(
        // Requirements
        4,                                  // Quest id (Must match database)
        "Meet every one in the town!",    // Quest name
        "Go out and talk to everyone you see!", // Desc
        2,                                  // Var id
        1,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        50,                                 // Exp
        30,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        1,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[3] = Quest(
        // Requirements
        3,                                  // Quest id (Must match database)
        "Buy a small HP potion!",    // Quest name
        "Small HP Potion can be bought from Ryn's store!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        1,                                  // Item id
        1,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        10,                                 // Exp
        10,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[2] = Quest(
        // Requirements
        2,                                  // Quest id (Must match database)
        "Collect 5 blue slime phlegms!",    // Quest name
        "Slime phlegms can be collected through defeating the blue slime in the north of the town!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        2,                                  // Item id
        5,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        50,                                 // Exp
        10,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );
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
