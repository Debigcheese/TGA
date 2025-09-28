#include "Chest.h"

Chest::Chest(int aRoomId, Rarity aRarity, const std::vector<Item>& aItems) : myRoomId(aRoomId),
                                                                             myName(GetNameFromRarity()),
                                                                             myIsOpen(false),
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

std::string Chest::GetNameFromRarity() const
{
	switch (myRarity)
	{
		case Rarity::None:
		{
			return "";
		}
		case Rarity::Bronze:
		{
			return "Wooden chest";
		}
		case Rarity::Silver:
		{
			return "Silver chest";
		}
		case Rarity::Gold:
		{
			return "Gold chest";
		}
		case Rarity::Legendary:
		{
			return "Legendary chest";
		}
	}
	return "Wooden chest";
}

std::string Chest::GetName() const
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
