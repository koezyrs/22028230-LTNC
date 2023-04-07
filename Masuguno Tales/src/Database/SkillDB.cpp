#include "SkillDB.h"

std::map<std::string, SkillType> SkillDB::skillDatabase;

void SkillDB::LoadSkillDatabase()
{
    skillDatabase["BasicAttack"] = SkillType("BasicAttack", "BasicAttack", "Skill-Basic Attack",
                                              5, 10, 0, 2000, 33);
}
