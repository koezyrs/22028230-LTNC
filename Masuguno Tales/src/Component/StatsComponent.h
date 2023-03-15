#pragma once
#ifndef StatsComponent_h
#define StatsComponent_h

class StatsComponent
{
public:
    StatsComponent(int _level, int _experience, int _experienceToNextLevel, int _maxHealth, int _health, int _maxMana, int _mana, int _damage, int _defense, int _attackSpeed)
    : Level(_level), Experience(_experience), ExperienceToNextLevel(_experienceToNextLevel), MaxHealth(_maxHealth), Health(_health),
    MaxMana(_maxMana), Mana(_mana), Damage(_damage), Defense(_defense), AttackSpeed(_attackSpeed)
    {}
    ~StatsComponent() {}
    int getLevel() const {return Level;}
    int getExperience() const {return Experience;}
    int getExperienceToNextLevel() const {return ExperienceToNextLevel;}
    int getMaxHealth() const {return MaxHealth;}
    int getHealth() const {return Health;}
    int getMaxMana() const {return MaxMana;}
    int getMana() const {return Mana;}
    int getDamage() const {return Damage;}
    int getDefense() const {return Defense;}
    int getAttackSpeed() const {return AttackSpeed;}

    void setLevel(int _level) {Level = _level;}
    void setExperience(int _experience) {Experience = _experience;}
    void setExperienceToNextLevel(int _experienceToNextLevel) {ExperienceToNextLevel = _experienceToNextLevel;}
    void setMaxHealth(int _maxHealth) {MaxHealth = _maxHealth;}
    void setMaxMana(int _maxMana) {MaxMana = _maxMana;}
    void setHealth(int _health) {Health = _health;}
    void setMana(int _mana) {Mana = _mana;}
    void setDamage(int _damage) {Damage = _damage;}
    void setDefense(int _defense) {Defense = _defense;}
    void setAttackSpeed(int _attackSpeed) {AttackSpeed = _attackSpeed;}

private:
    int Level;
    int Experience;
    int ExperienceToNextLevel;
    int Health;
    int MaxHealth;
    int Mana;
    int MaxMana;
    int Damage;
    int Defense;
    int AttackSpeed;
};

#endif // StatsComponent_h
