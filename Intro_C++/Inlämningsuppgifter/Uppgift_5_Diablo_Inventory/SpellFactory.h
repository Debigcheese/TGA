#pragma once
#include "GameEnums.h"
#include "Spell.h"
#include "SpellType.h"
#include <vector>

class SpellFactory
{
public:
	SpellFactory();
	void InitFactory();
	Spell Create(SpellKey aKey);
	static SpellFactory& GetFactory();


	std::vector<SpellKey> GetSpellKeysFromRarities(const std::vector<Rarity>& aRarities) const;
	std::vector<Spell> CreateSpellsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const;

private:
	std::vector<SpellType> myTypes;
	int myNextId;
};
