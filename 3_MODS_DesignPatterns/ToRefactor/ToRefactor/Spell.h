#pragma once
#include <string>


class Game;
class Actor;

class Spell
{
public:
    std::string myName;
    int cost;
    Spell(std::string name, int cost) : myName(name), cost(cost) {}
    virtual bool Cast(Game* game, Actor* caster, int targetX, int targetY) = 0;
};

class Fireball : public Spell
{
public:
    Fireball() : Spell("Fireball", 10) {}
    bool Cast(Game* game, Actor* caster, int targetX, int targetY) override;
};

class Heal : public Spell
{
public:
    Heal() : Spell("Heal", 8) {}
    bool Cast(Game* game, Actor* caster, int targetX, int targetY) override;
};
