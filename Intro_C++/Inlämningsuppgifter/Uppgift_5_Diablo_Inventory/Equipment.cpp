#include "Equipment.h"

#include <algorithm>
#include <iostream>

Equipment::Equipment()
{
	myEquipment.fill(nullptr);
}

void Equipment::AddItem(const Item& aItem)
{
	int index = FindFirstFreeSlot(aItem.GetItemAttributes().type);
	if (index < 0)
	{
		return;
	}
	myItems.push_back(std::make_unique<Item>(aItem));
	myEquipment[index] = myItems.back().get();
	PrintItemEquipped(index);
	UpdateAttributes();
}

void Equipment::RemoveItem(int aSlotIndex)
{
	if (aSlotIndex < 0 || aSlotIndex >= EQUIP_SLOTS_SIZE)
	{
		return;
	}
	Item* ptr = myEquipment[aSlotIndex];
	if (!ptr)
	{
		return;
	}

	auto it = std::find_if(myItems.begin(), myItems.end(),
	                       [ptr](const std::unique_ptr<Item>& item)
	                       {
		                       return item.get() == ptr;
	                       });

	PrintItemUnequipped(aSlotIndex); // has to print before clearing
	myEquipment[aSlotIndex] = nullptr; // clear slot

	if (it != myItems.end())
	{
		myItems.erase(it); // delete
	}

	UpdateAttributes();
}

float Equipment::GetItemsWeight() const
{
	float totalWeight = 0;
	for (const auto& item : myItems)
	{
		totalWeight += item->GetItemAttributes().weight;
	}
	return totalWeight;
}


bool Equipment::CanEquipItem(const Item& aItem) const
{
	const auto type = aItem.GetItemAttributes().type;

	int target = FindFirstFreeSlot(type);
	return target >= 0;
}

int Equipment::FindFirstFreeSlot(EquipmentType t) const
{
	for (int i = 0; i < EQUIP_SLOTS_SIZE; ++i)
	{
		if (SLOT_IDX[i].type == t && myEquipment[i] == nullptr)
		{
			return i;
		}
	}

	return -1;
}

const Item* Equipment::GetItemPtrAt(int slotIdx) const
{
	if (slotIdx < 0 || slotIdx >= Equipment::EQUIP_SLOTS_SIZE)
	{
		return nullptr;
	}

	return myEquipment[slotIdx];
}

void Equipment::UpdateAttributes()
{
	myAttributes.Clear();
	for (const auto& item : myItems)
	{
		myAttributes += item->GetAttributes();
	}
}

const Attributes& Equipment::GetAttributes() const
{
	return myAttributes;
}

void Equipment::PrintEquipment() const
{
	std::cout << "\n";
	for (int i = 0; i < EQUIP_SLOTS_SIZE; i++)
	{
		std::cout << i + 1 << ") " << SLOT_IDX[i].name << ": ";

		if (myEquipment[i])
		{
			myEquipment[i]->PrintItemName();
		}
		else
		{
			std::cout << "[-]";
		}

		std::cout << "\n";
	}
}

void Equipment::PrintItemEquipped(int aIndex) const
{
	std::cout << "\n";
	if (myEquipment[aIndex])
	{
		myEquipment[aIndex]->PrintItemName();
	}
	std::cout << " has been equipped\n";
}

void Equipment::PrintItemUnequipped(int aIndex) const
{
	std::cout << "\n";
	if (myEquipment[aIndex])
	{
		myEquipment[aIndex]->PrintItemName();
	}
	std::cout << " has been unequipped\n";
}
