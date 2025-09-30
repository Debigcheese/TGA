#include "ItemDB.h"

const ItemAttributes& ItemDB::GetDef(int aId)
{
	for (const auto& a : ITEM_DEF)
	{
		if (a.id == aId)
		{
			return a;
		}
	}
	return ITEM_DEF[aId];
}

int ItemDB::GetItemCount()
{
	return std::size(ITEM_DEF);
}

std::vector<int> ItemDB::GetIdsFromRarities(const std::vector<Rarity>& aRarities)
{
	std::vector<int> idsWithRarity;
	for (const auto& a : ITEM_DEF)
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
