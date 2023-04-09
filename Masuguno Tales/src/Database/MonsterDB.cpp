#include "MonsterDB.h"

std::map<std::string, MonsterType> MonsterDB::monsterDatabase;

// Name, Sprite, Damage, Health, Attack Speed, Chase Speed, RoamSpeed, Attack Range, Stop Chase Range;

void MonsterDB::LoadMonsterDatabase()
{
    monsterDatabase["Monster01"] = MonsterType("Cow Lv.1", "Sprite-MonsterCow",
                                    10.0f, 20.0f, 2000.0f, 0.5f, 0.2f, 46.0f, 128.0f);
}
