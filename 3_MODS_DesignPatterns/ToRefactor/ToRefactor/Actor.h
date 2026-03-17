#pragma once
#include <string>
#include <vector>
#include "Spell.h"
#include "ITargetable.h"

class Game;
class Component;

class Actor : public ITargetable
{
public:
	int myX;
	int myY;
	std::string myName;
	bool myIsActive;
	std::vector<Component*> myComponents;

	Actor(std::string name, int x, int y) : myName(name), myX(x), myY(y), myIsActive(true)
	{
	}

	~Actor();

	void AddComponent(Component* comp);
	void Update(Game* game);

	template <typename T>
	T* GetComponent();

	bool IsTargetable() const override { return true; }

	friend class Game;
};


template <typename T>
T* Actor::GetComponent()
{
	for (Component* c : myComponents)
	{
		T* target = dynamic_cast<T*>(c);
		if (target != NULL) return target;
	}
	return NULL;
}

class PlayerActor : public Actor
{
public:
	std::vector<Spell*> mySpells;
	Spell* myCurrentSpell;
	PlayerActor(int x, int y);
	~PlayerActor();
};

class MonsterActor : public Actor
{
public:
	bool isAggressive;
	MonsterActor(std::string name, int x, int y, bool agg);
};

class GoblinActor : public MonsterActor
{
public:
	GoblinActor(int x, int y);
};

class FireImpActor : public MonsterActor
{
public:
	FireImpActor(int x, int y);
};

class TrapActor : public Actor
{
public:
	TrapActor(int x, int y);
};
