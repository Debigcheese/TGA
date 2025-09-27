#include "Utils.h"
#include "ItemDB.h"
#include <iostream>

const ItemAttributes& ItemDB::GetDef(int aId)
{
	for (const auto& a : ItemDef)
	{
		if (a.id == aId)
		{
			return a;
		}
	}
	return ItemDef[aId];
}

int ItemDB::GetItemCount()
{
	return std::size(ItemDef);
}

std::vector<int> ItemDB::GetIdsFromRarities(const std::vector<Rarity>& aRarities)
{
	std::vector<int> idsWithRarity;
	for (const auto& a : ItemDef)
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
