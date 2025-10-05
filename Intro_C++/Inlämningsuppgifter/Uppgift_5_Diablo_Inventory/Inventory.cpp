#include "Inventory.h"

#include <iostream>

Inventory::Inventory()
	: myEquipment(), myItems()
{
}

void Inventory::AddItem(const Item& aItem)
{
	if (myEquipment.CanEquipItem(aItem))
	{
		myEquipment.AddItem(aItem);
	}
	else
	{
		myItems.push_back(aItem);
	}
}

void Inventory::RemoveItem(int aIndex)
{
	myItems.erase(myItems.begin() + aIndex);
}

float Inventory::GetItemsWeight() const
{
	float totalWeight = 0;
	if (myItems.empty())
	{
		return totalWeight;
	}
	for (const auto& item : myItems)
	{
		totalWeight += item.GetItemAttributes().weight;
	}
	return totalWeight;
}

void Inventory::UnequipItem(const Item& aItem, int aIndex)
{
	AddItem(aItem);
	myEquipment.RemoveItem(aIndex);
}

void Inventory::EquipItem(const Item& aItem, int aIndex)
{
	myEquipment.AddItem(aItem);
	RemoveItem(aIndex);
}

Equipment Inventory::GetEquipment() const
{
	return myEquipment;
}

float Inventory::GetInventoryWeight() const
{
	return GetItemsWeight() + GetEquipment().GetItemsWeight();
}

void Inventory::PrintInventory(float aCarryCapacity) const
{
	std::cout << "\n<--- Inventory ("
		<< std::lround(GetInventoryWeight()) << "/"
		<< std::lround(aCarryCapacity) << "kg) --->\n";

	if (myItems.empty())
	{
		std::cout << "Empty...\n";
	}

	for (size_t i = 0; i < myItems.size(); i++)
	{
		std::cout << i + 1 << ") ";
		myItems[i].PrintItemName();
		std::cout << "\n";
	}
}

void Inventory::PrintItemAdded(const Item& aItem) const
{
	std::cout << "\n";
	aItem.PrintItemName();
	std::cout << " has been added to your inventory!\n";
}
