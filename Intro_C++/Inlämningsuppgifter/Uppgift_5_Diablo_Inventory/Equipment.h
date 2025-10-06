#pragma once
#include <memory>

#include "Item.h"
#include "GameStructs.h"
#include <vector>
#include <string>

class Equipment
{
public:
	Equipment();
	void AddItem(const Item& aItem);
	void RemoveItem(int aIndex);

	float GetItemsWeight() const;
	const Item& GetItemAt(int aIndex) const;
	const std::vector<std::unique_ptr<Item>>& GetItems() const { return myItems; }
	const std::array<Item*, static_cast<int>(EquipmentType::Count)>& GetEquipment() const { return myEquipment; }

	bool CanEquipItem(const Item& aItem) const;
	int FindFirstFreeSlot(EquipmentType t) const;

	void UpdateAttributes();
	const Attributes& GetAttributes() const;

	void PrintEquipment() const;
	void PrintItemEquipped(int aIndex) const;
	void PrintItemUnequipped(int aIndex) const;

private:
	static constexpr int EQUIP_SLOTS_SIZE = static_cast<int>(EquipmentType::Count);

	struct EquipmentSlot
	{
		const EquipmentType type;
		std::string name;
	};

	std::array<Item*, EQUIP_SLOTS_SIZE> myEquipment;
	std::vector<std::unique_ptr<Item>> myItems;
	Attributes myAttributes{};

	//CONSTANTS
	const EquipmentSlot SLOT_IDX[EQUIP_SLOTS_SIZE] =
	{
		{EquipmentType::Head, "Head"},
		{EquipmentType::Hand, "Right Hand"},
		{EquipmentType::Hand, "Left Hand"},
		{EquipmentType::Body, "Body"},
		{EquipmentType::Legs, "Legs"},
		{EquipmentType::Feet, "Feet"},
		{EquipmentType::Amulet, "Amulet"},
	};
};
