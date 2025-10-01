#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "Spell.h"
#include "Utils.h"
#include <vector>

class SpellFactory
{
public:
	static SpellFactory& GetFactory();
	SpellFactory();
	Spell Create(const SpellKey aKey);

	std::vector<SpellKey> GetSpellKeysFromRarities(const std::vector<Rarity>& aRarities) const;
	std::vector<Spell> CreateSpellsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const;

private:
	std::vector<SpellAttributes> myTypes;
};
