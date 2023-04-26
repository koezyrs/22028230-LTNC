#pragma once
#ifndef MonsterDB_h
#define MonsterDB_h

#include <map>
#include <string>

struct MonsterType{
    int monster_id;
    int width, height;
    std::string monsterName;
    std::string monsterSprite;
    float damage, health, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;
    MonsterType() {}
    MonsterType(int _monster_id, int _width, int _height, std::string _monsterName, std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                float _chaseSpeed, float _roamSpeed, float _attackRange, float _stopChaseRange)
    : monster_id(_monster_id), width(_width), height(_height), monsterName(_monsterName), monsterSprite(_monsterSprite), damage(_damage), health(_health),
    attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed), roamSpeed(_roamSpeed), attackRange(_attackRange),
    stopChaseRange(_stopChaseRange)
    {}
};

class MonsterDB
{
public:
    static void LoadMonsterDatabase();
    static std::map<int, MonsterType> monsterDatabase;
};

#endif // MonsterDB_h
