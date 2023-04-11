#include "SkillDB.h"

std::map<std::string, SkillType> SkillDB::skillDatabase;

void SkillDB::LoadSkillDatabase()
{
    skillDatabase["BasicAttack"] = SkillType("Basic Attack", "Icon-Basick Attack", "Skill-Basic Attack", 5, 10, 0, 2000, 46);
}
