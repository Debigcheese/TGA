#include "Equipment.h"

#include <algorithm>
#include <iostream>

Equipment::Equipment()
	: myEquippedSlots()
{
}

bool Equipment::CanEquipItem(const Item& aItem) const
{
	const auto itemType = aItem.GetItemAttributes().type;

	for (int i = 0; i < EQUIP_SLOTS_SIZE; ++i)
	{
		if (SLOT_IDX[i].type != itemType)
		{
			continue;
		}
		const auto it =
			std::find_if(myEquippedSlots.begin(), myEquippedSlots.end(),
			             [&](const auto& eq)
			             {
				             return eq.slotIdx == SLOT_IDX[i].slotIdx;
			             });

		bool occupied = (it != myEquippedSlots.end());
		if (!occupied)
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

std::vector<int> Equipment::FindPossibleSlotIdx(const Item& aItem) const
{
	std::vector<int> possibleIdx;
	for (const auto& slot : SLOT_IDX)
	{
		if (slot.type == aItem.GetItemAttributes().type)
		{
			possibleIdx.push_back(slot.slotIdx);
		}
	}
	return possibleIdx;
}

bool Equipment::IsSlotFree(const Item& aItem)
{
	std::vector<int> possibleIds = FindPossibleSlotIdx(aItem);

	for (int i = 0; i < EQUIP_SLOTS_SIZE; ++i)
	{
	}

	return false;
}

int Equipment::FindFirstFreeSlot(EquipmentType t) const
{
	for (int i = 0; i < EQUIP_SLOTS_SIZE; ++i)
		if (SLOT_IDX[i].type == t && myEquippedIndex[SLOT_IDX[i].slotIdx] == -1)
			return SLOT_IDX[i].slotIdx;
	return -1;
}

bool Equipment::AutoEquip(const Item& item)
{
	const auto t = item.GetItemAttributes().type;

	int target = -1;
	for (int i = 0; i < EQUIP_SLOTS_SIZE; ++i)
		if (SLOT_IDX[i].type == t && myEquippedIndex[SLOT_IDX[i].slotIdx] == -1)
		{
			target = SLOT_IDX[i].slotIdx;
			break;
		}
	if (target < 0) return false;

	const int newIdx = static_cast<int>(myItems.size());
	myItems.push_back(item);
	myEquippedIndex[target] = newIdx;
	PrintItemEquipped(item);
	UpdateAttributes();
	return true;
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
		std::cout << i + 1 << ") " << SLOT_IDX[i].name << ": ";

		const auto it =
			std::find_if(myEquippedSlots.begin(), myEquippedSlots.end(),
			             [&](const auto& eq)
			             {
				             return eq.slotIdx == SLOT_IDX[i].slotIdx;
			             });

		bool occupied = (it != myEquippedSlots.end());

		int idx = myEquippedSlots[i];

		if (it != myEquippedSlots.end())
		{
			myItems[idx].PrintItemName();
		}
		else
		{
			std::cout << "[-]";
		}

		if (static_cast<int>(myEquippedSlots.size()) <= i)
		{
			if (SLOT_IDX[i].slotIdx == myEquippedSlots[i].slotIdx && !myEquippedSlots.empty())
			{
				myItems[i].PrintItemName();
			}
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
