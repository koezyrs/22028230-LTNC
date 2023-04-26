#include "MonsterDB.h"

std::map<int, MonsterType> MonsterDB::monsterDatabase;

//ID,   Width, Height ,Name, Sprite, Damage, Health, Attack Speed, Chase Speed, RoamSpeed, Attack Range, Stop Chase Range;

void MonsterDB::LoadMonsterDatabase()
{
    monsterDatabase[1] = MonsterType(1, 32, 32, "Cow Lv.1", "Sprite-MonsterCow",
                                    10.0f, 20.0f, 2000.0f, 0.5f, 0.2f, 46.0f, 128.0f);
    monsterDatabase[2] = MonsterType(2, 192, 192, "Boss Dragon Lv.100", "Sprite-BossDragon",
                                    10.0f, 200.0f, 2000.0f, 1.0f, 0.5f, 70.0f, 500.0f);
}
