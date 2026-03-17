#include "Actor.h"
#include "Component.h"
#include "StatsComponent.h"

Actor::~Actor()
{
    for (Component* c : myComponents) delete c;
}

void Actor::AddComponent(Component* comp)
{
    comp->myOwner = this;
    myComponents.push_back(comp);
}

void Actor::Update(Game* game)
{
    for (Component* c : myComponents) c->Update(game);
}


PlayerActor::PlayerActor(int x, int y) : Actor("Player", x, y), myCurrentSpell(nullptr)
{
    AddComponent(new StatsComponent(100, 10, 5, 20));
    AddComponent(new PlayerInputComponent());
    AddComponent(new RenderComponent('@'));
    AddComponent(new InventoryComponent(3));

    mySpells.push_back(new Fireball());
    mySpells.push_back(new Heal());
    myCurrentSpell = mySpells[0];
}
PlayerActor::~PlayerActor() {
    for (Spell* s : mySpells) delete s;
}


MonsterActor::MonsterActor(std::string name, int x, int y, bool agg)
    : Actor(name, x, y), isAggressive(agg)
{}

GoblinActor::GoblinActor(int x, int y) : MonsterActor("Goblin", x, y, true) 
{
    AddComponent(new StatsComponent(30, 5, 2));
    AddComponent(new MonsterAIComponent());
    AddComponent(new RenderComponent('g'));
}

FireImpActor::FireImpActor(int x, int y) : MonsterActor("Fire Imp", x, y, false) 
{
    AddComponent(new FireImpStatsComponent(20, 7, 1));
    AddComponent(new MonsterAIComponent());
    AddComponent(new RenderComponent('f'));
}

TrapActor::TrapActor(int x, int y) : Actor("Trap Entity", x, y) 
{
    AddComponent(new StatsComponent(1, 0, 0));
    AddComponent(new RenderComponent('^'));
}