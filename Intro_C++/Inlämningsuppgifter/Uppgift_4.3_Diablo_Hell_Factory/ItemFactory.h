#pragma once
#include "GameEnums.h"
#include "Item.h"
#include "Utils.h"
#include "ItemType.h"
#include <vector>

class ItemFactory
{
public:
	static ItemFactory& GetFactory();
	ItemFactory();
	Item Create(const ItemKey aKey);
	void InitFactory();

	std::vector<ItemKey> GetItemKeysFromRarities(const std::vector<Rarity>& aRarities) const;
	std::vector<Item> CreateItemsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const;

private:
	std::vector<ItemType> myTypes;
};
