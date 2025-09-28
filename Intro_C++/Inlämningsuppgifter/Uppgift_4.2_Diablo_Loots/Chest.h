#pragma once
#include "Item.h"
#include <vector>

class Chest
{
public:
	Chest(int aRoomId, const std::vector<Item>& aItems);
	std::vector<Item> Open();

	const char* GetName() const;
	bool GetIsOpen() const;
	std::vector<Item> GetItemsInChest() const;
	std::vector<Item>& GetItemsInChest();

private:
	int myRoomId = 0;
	const char* myName = "Wooden chest";
	bool myIsOpen;
	std::vector<Item> myItems;
};
