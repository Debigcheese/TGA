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
	myAttributes.id = aNewId;
}

void Item::PrintItemOnPickup() const
{
	std::cout << GetColorCode(GetColorFromRarity(myAttributes.rarity), true)
		<< "\n<------ " << RarityToString(myAttributes.rarity) << " ------>"
		<< GetColorCode(GetColorFromRarity(myAttributes.rarity), false)
		<< "\n"
		<< "[" << myAttributes.name << "]" << "\n";

	// Print non-zero attributes
	const Attributes& a = myAttributes.attributes;
	if (a.strength != 0)       std::cout << "Strength: " << a.strength << "\n";
	if (a.agility != 0)        std::cout << "Agility: " << a.agility << "\n";
	if (a.endurance != 0)      std::cout << "Endurance: " << a.endurance << "\n";
	if (a.maxHealth != 0)      std::cout << "Max Health: " << a.maxHealth << "\n";
	if (a.currentHealth != 0)  std::cout << "Current Health: " << a.currentHealth << "\n";
	if (a.carryCapacity != 0)  std::cout << "Carry Capacity: " << a.carryCapacity << "\n";
	if (a.damage != 0)         std::cout << "Damage: " << a.damage << "\n";
	if (a.defense != 0)        std::cout << "Defense: " << a.defense << "\n";
	std::cout << "\n";

}

void Item::PrintItemAttributes() const
{
	std::cout << "";
}
