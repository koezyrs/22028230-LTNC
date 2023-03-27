#pragma once
#ifndef StatsComponent_h
#define StatsComponent_h

#include "../Settings.h"

class StatsComponent
{
public:
    StatsComponent(int _level, int _experience, int _experienceToNextLevel, int _maxHealth, int _health, int _maxMana, int _mana, int _damage, int _defense, int _attackSpeed)
    : Level(_level), Experience(_experience), ExperienceToNextLevel(_experienceToNextLevel), Health(_health), MaxHealth(_maxHealth),
    Mana(_mana), MaxMana(_maxMana), Damage(_damage), Defense(_defense), AttackSpeed(_attackSpeed)
    {}
    ~StatsComponent() {}

    void Update()
    {
        if(Health <= 0) Health = 0;
        if(Mana <= 0) Mana = 0;
        if(Health >= MaxHealth) Health = MaxHealth;
        if(Mana >= MaxMana) Mana = MaxMana;

        if(Level >= MAX_LEVEL)
        {
            Level = MAX_LEVEL;
            Experience = ExperienceToNextLevel;
        }else{
            if(Experience >= ExperienceToNextLevel)
            {
                Experience = Experience - ExperienceToNextLevel;
                Level = Level + 1;
                ExperienceToNextLevel = ExperienceToNextLevel + ExperienceToNextLevel*NEXT_LEVEL_EXP_RATE;
            }
        }
    }

    int Level = 0;
    int Experience = 0;
    int ExperienceToNextLevel = 0;
    int Health = 0;
    int MaxHealth = 0;
    int Mana = 0;
    int MaxMana = 0;
    int Damage = 0;
    int Defense = 0;
    int AttackSpeed = 0;
};

#endif // StatsComponent_h
