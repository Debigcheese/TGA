#pragma once
#include "Item.h"
#include <vector>
#include <string>

class Chest
{
public:
	Chest(int aRoomId, Rarity aRarity, const std::vector<Item>& aItems);
	std::vector<Item> Open();

	std::string GetNameFromRarity() const;
	std::string GetName() const;
	bool GetIsOpen() const;
	std::vector<Item> GetItemsInChest() const;
	std::vector<Item>& GetItemsInChest();

private:
	int myRoomId = 0;
	std::string myName;
	bool myIsOpen;
	Rarity myRarity;
	std::vector<Item> myItems;
};
