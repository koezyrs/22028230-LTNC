#include "StatsComponent.h"

StatsComponent::StatsComponent(int _level, int _experience, int _experienceToNextLevel,int _strength, int _dexterity, int _intelligence,
                   int _vitality, int _agility)
: Level(_level), Experience(_experience), ExperienceToNextLevel(_experienceToNextLevel), Strength(_strength),
Dexterity(_dexterity), Intelligence(_intelligence), Vitality(_vitality), Agility(_agility)
{
    Damage = _strength*2;
    Defense = _dexterity*0.5;
    MaxMana = _intelligence*3;
    MaxHealth = _vitality*5;
    AttackSpeed = _agility;

    Mana = MaxMana;
    Health = MaxHealth;
}

StatsComponent::~StatsComponent() {}

void StatsComponent::Update()
{
    Damage = Strength*2;
    Defense = Dexterity*0.5;
    MaxMana = Intelligence*3;
    MaxHealth = Vitality*5;
    AttackSpeed = Agility;

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

void StatsComponent::ApplyDamage(int _damage)
{
    float LO = 0.8f;
    float HI = 1.8f;
    float D = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    int healthLose = (_damage - Defense) * D;

    if(healthLose <= 0) return;
    if(Health - healthLose <= 0) Health = 0;
    else Health -= healthLose;
}
