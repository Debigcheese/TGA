#pragma once
#include "Equipment.h"
#include "Item.h"

#include <vector>

class Inventory
{
public:
	Inventory();
	void AddItem(const Item& aItem);
	void RemoveItem(int aItemId);
	const Item& GetItemAt(int aIndex) const;
	const std::vector<Item>& GetItems() const { return myItems; }
	float GetItemsWeight() const;
	float GetInventoryWeight() const;
	const Equipment& GetEquipment() const { return myEquipment; }
	std::string ToString(EquipmentType type) const;

	void DropItem(int aItemId);
	void UnequipItem(int aSlotIndex);
	void EquipItem(int aItemId);

	void PrintInventory(float aCarryCapacity) const;
	void PrintItemAdded(const Item& aItem) const;

private:
	Equipment myEquipment;
	std::vector<Item> myItems;
};
