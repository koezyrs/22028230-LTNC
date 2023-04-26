#include "QuestLog.h"
std::map<int,int> QuestLog::mVariable;
std::map<int,int> QuestLog::totalMonsterKilled;
std::map<int,bool> QuestLog::onGoingQuest;
std::map<int,bool> QuestLog::finishedQuest;

QuestLog::QuestLog()
{

}

QuestLog::~QuestLog()
{

}

bool QuestLog::giveQuest(int quest_id)
{

    if(QuestDB::questDatabase.count(quest_id) <= 0)
    {
        std::cerr << "Can not found quest id:" << quest_id << std::endl;
        return false;
    }

    Quest quest = QuestDB::questDatabase[quest_id];
    if((finishedQuest.count(quest_id) > 0) && !quest.repeat)
    {
        std::cerr << "Quest was completed! Can not take again!" << std::endl;
        return false;
    }
    if(onGoingQuest.count(quest_id) > 0)
    {
        std::cerr << "Quest has already being accepted!" << std::endl;
        return false;
    }

    onGoingQuest[quest_id] = true;
    if(totalMonsterKilled.count(quest.enemy_id) <= 0) totalMonsterKilled[quest.enemy_id] = 0;
    std::cerr << "Quest "<< quest.name << " was given!" << std::endl;
    return true;
}

void QuestLog::dropQuest(int quest_id)
{
    Quest quest = QuestDB::questDatabase[quest_id];
}

bool QuestLog::checkQuest(int quest_id)
{
    if(QuestDB::questDatabase.count(quest_id) <= 0)
    {
        std::cerr << "Can not found quest id:" << quest_id << std::endl;
        return false;
    }

    if(onGoingQuest.count(quest_id) <= 0)
    {
        std::cerr << "You haven't claim the quest yet!" << std::endl;
        return false;
    }

    bool success = true;
    Quest quest = QuestDB::questDatabase[quest_id];

    if((mVariable[quest.variable_id] < quest.variable_amount) && (quest.variable_id > 0))
    {
        std::cerr << "Doesn't match variable requirements!" << std::endl;
        success = false;
    }

    if(quest.item_id > 0)
    {
        bool tmp = success;
        success = Game::gInventory->FindItem(quest.item_id, quest.item_amount);
        if(!success && tmp) std::cerr << "Doesn't match item requirements!" << std::endl;
    }
    if(quest.equip_id > 0)
    {
        bool tmp = success;
        success = Game::gInventory->FindEquip(quest.equip_id, quest.equip_amount);
        if(!success && tmp) std::cerr << "Doesn't match equipment requirements!" << std::endl;
    }

    if((totalMonsterKilled[quest.enemy_id] < quest.enemy_amount) && (quest.enemy_id > 0))
    {
        success = false;
        std::cerr << "Doesn't match monster requirements!" << std::endl;
    }

    if(success)
    {
        Game::gPlayer->mStats->Experience += quest.reward_exp;
        Game::gInventory->AddGold(quest.reward_gold);
        for(int i = 1; i <= quest.reward_item_amount; i++) Game::gInventory->AddItem(quest.reward_item_id);
        for(int i = 1; i <= quest.reward_equip_amount; i++) Game::gInventory->AddEquipment(quest.reward_equip_id);
        totalMonsterKilled[quest.enemy_id] = 0;
        onGoingQuest[quest_id] = false;
        if(!quest.repeat) finishedQuest[quest_id] = true;
        std::cerr << "Finished quest and received reward!" << std::endl;
    }
    return success;
}
