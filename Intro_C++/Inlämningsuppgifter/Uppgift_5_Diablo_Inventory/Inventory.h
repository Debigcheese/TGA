#pragma once
#include "Equipment.h"
#include "Item.h"

#include <vector>

class Inventory
{
public:
	Inventory();
	void AddItem(const Item& aItem);
	void RemoveItem(int aIndex);
	const std::vector<Item>& GetItems() const { return myItems; }
	float GetItemsWeight() const;
	float GetInventoryWeight() const;

	void UnequipItem(const Item& aItem, int aIndex);
	void EquipItem(const Item& aItem, int aIndex);
	Equipment GetEquipment() const;

	void PrintInventory(float aCarryCapacity) const;
	void PrintItemAdded(const Item& aItem) const;

private:
	Equipment myEquipment;
	std::vector<Item> myItems;
};
