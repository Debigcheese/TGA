#pragma once
#include "GameStructs.h"

class Player;

class Spell
{
public:
	Spell(const SpellAttributes& aAttributes);
	void UpdateOnHitCount();

	const char* GetName() const;
	SpellAttributes GetAttributes() const;
	bool GetSpellFinished() const;

	void PrintSpellAttributes() const;
	void PrintSpellOnPickup() const;
	void PrintSpellOnDisplay() const;
	void PrintSpellName() const;

private:
	//CONSTANTS
	static constexpr int DEFAULT_ON_HIT_COUNT = 10;

	int myOnHitCount;
	SpellAttributes myAttributes;
};
