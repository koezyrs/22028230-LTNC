#include "QuestDB.h"

std::map<int, Quest> QuestDB::questDatabase;

void QuestDB::LoadQuestDatabase()
{
    questDatabase[1] = Quest(
        // Requirements
        "Beginner Quest",                   // Quest name
        "Hi this is your first quest!",     // Desc
        0,                                  // Var id
        0,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        10,                                 // Exp
        1,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );

}

void QuestDB::giveQuest(int quest_id)
{
    Quest quest = questDatabase[quest_id];
}

void QuestDB::dropQuest(int quest_id)
{
    Quest quest = questDatabase[quest_id];
}

bool QuestDB::checkQuest(int quest_id)
{
    bool success = true;
    Quest quest = questDatabase[quest_id];
    if(Game::gPlayer->mVariable[quest.variable_id] != quest.variable_amount) success = false;
    success = Game::gInventory->FindItem(quest.item_id, quest.item_amount);
    success = Game::gInventory->FindEquip(quest.equip_id, quest.equip_amount);

    if(success)
    {
        Game::gPlayer->mStats->Experience += quest.reward_exp;
        //Game::gInventory->AddGold(quest.reward_gold);
        for(int i = 1; i <= quest.reward_item_amount; i++) Game::gInventory->AddItem(quest.reward_item_id);
        for(int i = 1; i <= quest.reward_equip_amount; i++) Game::gInventory->AddEquipment(quest.reward_equip_id);
    }
    return true;
}
