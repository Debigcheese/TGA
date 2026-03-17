#pragma once

#include <vector>

#include "Command.h"
#include "Spell.h"

class Game;
class Actor;

class Component
{
public:
	Actor* myOwner;

	virtual ~Component()
	{
	}

	virtual void Update(Game* game)
	{
	}
};

class PlayerInputComponent : public Component
{
public:
	int m_tempMoveX;
	int m_tempMoveY;
	std::vector<MoveCommand*> myMoveCommands;

	bool HandleInput(Game* game, char input);
};

class MonsterAIComponent : public Component
{
public:
	void Update(Game* game) override;
};

class RenderComponent : public Component
{
public:
	char m_symbol;

	RenderComponent(char s) : m_symbol(s)
	{
	}
};

class InventoryComponent : public Component
{
public:
	int potions;

	InventoryComponent(int startPotions) : potions(startPotions)
	{
	}
};

class SpellbookComponent : public Component
{
public:
	std::vector<Spell*> mySpells;
	Spell* myCurrentSpell;

	SpellbookComponent() : myCurrentSpell(NULL)
	{
	}

	~SpellbookComponent()
	{
	}

	void AddSpell(Spell* spell);
};
