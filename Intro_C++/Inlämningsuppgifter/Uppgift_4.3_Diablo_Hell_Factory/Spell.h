#pragma once
#include "GameStructs.h"
#include "SpellType.h"

class Player;

class Spell
{
public:
	Spell(SpellType* aSpellType);
	void UpdateOnHitCount();

	SpellAttributes GetSpellAttributes() const { return mySpellType->GetSpellAttributes(); }
	Attributes GetAttributes() const { return GetSpellAttributes().attributes; }
	bool GetSpellFinished() const;

	void PrintSpellAttributes() const;
	void PrintSpellOnPickup() const;
	void PrintSpellOnDisplay() const;
	void PrintSpellName() const;

private:
	//CONSTANTS
	static constexpr int DEFAULT_ON_HIT_COUNT = 10;

	int myOnHitCount;
	SpellType* mySpellType;
};
