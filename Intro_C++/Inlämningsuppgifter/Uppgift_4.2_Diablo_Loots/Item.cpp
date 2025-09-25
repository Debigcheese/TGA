#include "Item.h"
#include "Player.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;
using namespace ItemDB;

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

std::vector<Item> ItemDB::GetItemsWithRarity(const std::vector<Rarity>& aItemRarities)
{
	std::vector<int> itemIdPool = ItemDB::GetIdsFromRarities(aItemRarities);

	const int RANDOM_SIZE = GenerateRandomNumber(0, 2);

	std::vector<Item> itemsInRoom = {};

	for (int i = 0; i < RANDOM_SIZE; ++i)
	{
		int randomIndex = GenerateRandomNumber(0, static_cast<int>(itemIdPool.size() - 1));
		int chosenId = itemIdPool[randomIndex];
		itemsInRoom.emplace_back(chosenId);
	}
	return itemsInRoom;
}

Item::Item(int aId) :
	myAttributes{
		GetDef(aId).id, GetDef(aId).type, GetDef(aId).rarity, GetDef(aId).name,
		GetDef(aId).weight, GetDef(aId).attributes
	}
{
}

void Item::SetId(int aNewId)
{
	myId = aNewId;
}

void Item::PrintItemAttributes() const
{
	std::cout << "";
}
