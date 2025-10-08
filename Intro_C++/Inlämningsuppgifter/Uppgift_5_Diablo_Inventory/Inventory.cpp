#include "Inventory.h"

#include <algorithm>
#include <iostream>

Inventory::Inventory()
	: myEquipment(), myItems()
{
}

void Inventory::AddItem(const Item& aItem)
{
	myItems.push_back(aItem);
}

void Inventory::RemoveItem(int aItemId)
{
	auto it = std::find_if(myItems.begin(), myItems.end(),
	                       [&](const Item& item)
	                       {
		                       return item.GetId() == aItemId;
	                       });
	if (it != myItems.end())
	{
		myItems.erase(it);
	}
}

const Item& Inventory::GetItemAt(int aIndex) const
{
	if (aIndex < 0 || aIndex >= static_cast<int>(myItems.size()))
	{
		std::cout << "\nIndex out of bounds";
		system("pause");
	}

	const auto& item = myItems[aIndex];
	return item;
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

void Inventory::DropItem(int aItemId)
{
	auto it = std::find_if(myItems.begin(), myItems.end(),
	                       [&](const Item& item)
	                       {
		                       return item.GetId() == aItemId;
	                       });
	if (it == myItems.end())
	{
		return;
	}
	std::cout << "\nYou dropped ";
	it->PrintItemName();
	std::cout << " on the floor\n";
	myItems.erase(it);
}

void Inventory::UnequipItem(int aSlotIndex)
{
	const auto* pEquipped = myEquipment.GetItemPtrAt(aSlotIndex);

	if (!pEquipped)
	{
		return;
	}
	const auto& temp = *pEquipped;
	AddItem(temp);
	myEquipment.RemoveItem(aSlotIndex);
}

void Inventory::EquipItem(int aItemId)
{
	auto it = std::find_if(myItems.begin(), myItems.end(),
	                       [&](const Item& item)
	                       {
		                       return item.GetId() == aItemId;
	                       });
	if (it == myItems.end())
	{
		return;
	}
	Item tempItem = *it;
	myEquipment.AddItem(tempItem);
	myItems.erase(it);
}

float Inventory::GetInventoryWeight() const
{
	return GetItemsWeight() + myEquipment.GetItemsWeight();
}

std::string Inventory::ToString(EquipmentType type) const
{
	switch (type)
	{
		case EquipmentType::Head:
		{
			return "Head";
		}
		case EquipmentType::Hand:
		{
			return "Hand";
		}
		case EquipmentType::Body:
		{
			return "Body";
		}
		case EquipmentType::Legs:
		{
			return "Legs";
		}
		case EquipmentType::Feet:
		{
			return "Feet";
		}
		case EquipmentType::Amulet:
		{
			return "Amulet";
		}
		default:
		{
			return "Unknown";
		}
	}
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
		std::cout << " (" << ToString(myItems[i].GetItemAttributes().type);
		std::cout << ")";
		std::cout << "\n";
	}
	std::cout << myItems.size() + 1 << ") Return\n";
}

void Inventory::PrintItemAdded(const Item& aItem) const
{
	std::cout << "\n";
	aItem.PrintItemName();
	std::cout << " has been added to your inventory!\n";
}
