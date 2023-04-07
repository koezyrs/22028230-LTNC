#pragma once
#ifndef SkillDB_h
#define SkillDB_h


#include <map>
#include <string>

struct SkillType{
    std::string skillName;
    std::string skillIcon;
    std::string skillSprite;
    int skillFrames;
    float damage, manaCost, cooldown;
    float skillRange;
    SkillType() {}
    SkillType(std::string _skillName, std::string _skillIcon, std::string _skillSprite, int _skillFrames, float _damage,
              float _manaCost, float _cooldown, float _skillRange)
    :skillName(_skillName), skillIcon(_skillIcon), skillSprite(_skillSprite), skillFrames(_skillFrames), damage(_damage),
    manaCost(_manaCost), cooldown(_cooldown), skillRange(_skillRange){}
};

class SkillDB
{
public:
    static void LoadSkillDatabase();
    static std::map<std::string, SkillType> skillDatabase;
};

#endif // SkillDB_h
