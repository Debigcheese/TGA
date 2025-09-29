#include "SpellDB.h"

const SpellAttributes& SpellDB::GetDef(int aId)
{
	for (const auto& a : SpellDB::SpellDef)
	{
		if (a.id == aId)
		{
			return a;
		}
	}
	return SpellDef[aId];
}

int SpellDB::GetItemCount()
{
	return std::size(SpellDef);
}

std::vector<int> SpellDB::GetIdsFromRarities(const std::vector<Rarity>& aRarities)
{
	std::vector<int> idsWithRarity;
	for (const auto& a : SpellDef)
	{
		for (const auto& r : aRarities)
		{
			if (a.rarity == r)
			{
				idsWithRarity.push_back(a.id);
			}
		}
	}
	return idsWithRarity;
}
