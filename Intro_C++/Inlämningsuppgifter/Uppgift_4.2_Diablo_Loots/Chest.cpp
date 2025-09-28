#include "Chest.h"

Chest::Chest(int aRoomId, const std::vector<Item>& aItems) : myRoomId(aRoomId), myName("Wooden Chest"), myIsOpen(false),
                                                             myItems(aItems)
{
}

std::vector<Item> Chest::Open()
{
	if (myIsOpen)
	{
		return {};
	}
	myIsOpen = true;
	return std::exchange(myItems, {});
}

const char* Chest::GetName() const
{
	return myName;
}

bool Chest::GetIsOpen() const
{
	return myIsOpen;
}

std::vector<Item> Chest::GetItemsInChest() const
{
	return myItems;
}

std::vector<Item>& Chest::GetItemsInChest()
{
	return myItems;
}
