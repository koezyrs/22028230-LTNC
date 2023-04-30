#include "MonsterDB.h"

std::map<int, MonsterType> MonsterDB::monsterDatabase;

//ID,   Width, Height ,Name, Sprite, Damage, Health, Attack Speed, Chase Speed, RoamSpeed, Attack Range, Stop Chase Range
// Exp , Gold, item_reward_id, item_drop_percent, equipment_reward_id, equipment_drop_percent;

void MonsterDB::LoadMonsterDatabase()
{
    monsterDatabase[3] = MonsterType(3, 32, 38, "Dummy", "Sprite-Dummy",
                                    0.0f, 15.0f, 10000.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                    0,0,0,0,0,0,true);
    monsterDatabase[1] = MonsterType(1, 32, 32, "Slime Lv.1", "Sprite-BlueSlime",
                                    10.0f, 30.0f, 3000.0f, 0.4f, 0.1f, 30.0f, 128.0f,
                                    15,5,1,1,0,0);
    monsterDatabase[2] = MonsterType(2, 32, 32, "Slime Lv.5", "Sprite-GreenSlime",
                                    17.0f, 100.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    25,10,0,0,0,0);
}
