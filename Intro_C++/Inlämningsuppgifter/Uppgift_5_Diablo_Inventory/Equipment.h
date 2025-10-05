#pragma once
#include "Item.h"
#include "GameStructs.h"
#include <vector>
#include <string>

class Equipment
{
public:
	Equipment();
	bool CanEquipItem(const Item& aItem) const;
	void AddItem(const Item& aItem);
	void RemoveItem(int aIndex);

	const std::vector<Item>& GetItems() const { return myItems; }
	float GetItemsWeight() const;

	void UpdateAttributes();
	const Attributes& GetAttributes() const;

	void PrintEquipment() const;
	void PrintItemEquipped(const Item& aItem) const;
	void PrintItemUnequipped(const Item& aItem) const;

private:
	struct EquipmentSlot
	{
		const EquipmentType type;
		std::string name;
		const int slotIdx;
	};

	Attributes myAttributes{};
	std::vector<EquipmentSlot> myEquippedSlots;
	std::vector<Item> myItems;

	//CONSTANTS
	static constexpr int EQUIP_SLOTS_SIZE = static_cast<int>(EquipmentType::Count);

	const EquipmentSlot SLOT_IDX[EQUIP_SLOTS_SIZE] =
	{
		{EquipmentType::Head, "Head", 0},
		{EquipmentType::Hand, "Right Hand", 1},
		{EquipmentType::Hand, "Left Hand", 2},
		{EquipmentType::Body, "Body", 3},
		{EquipmentType::Legs, "Legs", 4},
		{EquipmentType::Feet, "Feet", 5},
		{EquipmentType::Amulet, "Amulet", 6},
	};
};
