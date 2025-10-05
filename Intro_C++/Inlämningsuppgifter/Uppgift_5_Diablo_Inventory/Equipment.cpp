#include "Equipment.h"
#include <iostream>

Equipment::Equipment()
	: myEquippedSlots()
{
}

bool Equipment::CanEquipItem(const Item& aItem) const
{
	if (myEquippedSlots.empty())
	{
		return true;
	}
	for (const auto& equippedSlot : myEquippedSlots)
	{
		if (equippedSlot.type == aItem.GetItemAttributes().type && equippedSlot.slotIdx != SLOT_IDX->slotIdx)
		{
			return true;
		}
	}
	return false;
}

float Equipment::GetItemsWeight() const
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

void Equipment::UpdateAttributes()
{
	myAttributes.Clear();
	for (const auto& item : myItems)
	{
		myAttributes += item.GetAttributes();
	}
}

const Attributes& Equipment::GetAttributes() const
{
	return myAttributes;
}

void Equipment::AddItem(const Item& aItem)
{
	PrintItemEquipped(aItem);
	myItems.push_back(aItem);
	UpdateAttributes();
}

void Equipment::RemoveItem(int aIndex)
{
	const auto& item = myItems.at(aIndex);
	PrintItemUnequipped(item);
	myItems.erase(myItems.begin() + aIndex);
	UpdateAttributes();
}

void Equipment::PrintEquipment() const
{
	std::cout << "\n";
	for (int i = 0; i < EQUIP_SLOTS_SIZE; i++)
	{
		std::cout << i + 1 << ") "
			<< SLOT_IDX[i].name << ": ";
		if (static_cast<int>(myEquippedSlots.size()) <= i)
		{
			//if (SLOT_IDX[i].slotIdx == myEquippedSlots[i].slotIdx && !myEquippedSlots.empty())
			//{
			//	myItems[i].PrintItemName();
			//}
		}

		std::cout << "\n";
	}
}

void Equipment::PrintItemEquipped(const Item& aItem) const
{
	std::cout << "\n";
	aItem.PrintItemName();
	std::cout << " has been equipped\n";
}

void Equipment::PrintItemUnequipped(const Item& aItem) const
{
	std::cout << "\n";
	aItem.PrintItemName();
	std::cout << " has been unequipped\n";
}
