#include "QuestDB.h"

std::map<int, Quest> QuestDB::questDatabase;

void QuestDB::LoadQuestDatabase()
{
    questDatabase[1] = Quest(
        "Beginner Quest",
        "Hi this is your first quest",
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        10,
        1,
        0,
        0,
        0,
        0,
        false
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
    /*
    Quest quest = questDatabase[quest_id];
    bool success = true;
    if(Game::gPlayer->mVariable[quest.variable_id] != quest.variable_amount) success = false;
    success = Game::gInventory->FindItem(quest.item_id, quest.item_amount);
    success = Game::gInventory->FindEquip(quest.equip_id, quest.equip_amount);

    if(success)
    {
        Game::gPlayer->mStats->Experience += quest.reward_exp;
        Game::gInventory->AddGold(quest.reward_gold);
        for(int i = 1; i <= quest.reward_item_amount; i++) Game::gInventory->AddItem(reward_item_id);
        for(int i = 1; i <= quest.reward_equip_amount; i++) Game::gInventory->AddEquipment(reward_equip_id);
    }
    */
    return true;

}
