#include "Item.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

Item::Item(ItemType* myItemType)
	: myItemType(myItemType)
{
}

//
//const char* Item::GetName() const
//{
//	return myAttributes.name;
//}
//
//float Item::GetWeight() const
//{
//	return myAttributes.weight;
//}
//
//ItemAttributes Item::GetAttributes() const
//{
//	return myAttributes;
//}

void Item::PrintItemAttributes() const
{
	// Print non-zero attributes
	const Attributes& a = myItemType->GetAttributes();
	if (a.strength != 0.0f)
	{
		std::cout << "Strength: "
			<< GetPrefixSign(a.strength)
			<< a.strength << "\n";
	}
	if (a.agility != 0.0f)
	{
		std::cout << "Agility: "
			<< GetPrefixSign(a.agility)
			<< a.agility << "\n";
	}
	if (a.endurance != 0.0f)
	{
		std::cout << "Endurance: "
			<< GetPrefixSign(a.endurance)
			<< a.endurance << "\n";
	}
	if (a.maxHealth != 0.0f)
	{
		std::cout << "Max Health: "
			<< GetPrefixSign(a.maxHealth)
			<< a.maxHealth << "\n";
	}
	if (a.currentHealth != 0.0f)
	{
		std::cout << "Current Health: "
			<< GetPrefixSign(a.currentHealth)
			<< a.currentHealth << "\n";
	}
	if (a.carryCapacity != 0.0f)
	{
		std::cout << "Carry Capacity: "
			<< GetPrefixSign(a.carryCapacity)
			<< a.carryCapacity << "\n";
	}
	if (a.damage != 0.0f)
	{
		std::cout << "Damage: "
			<< GetPrefixSign(a.damage)
			<< a.damage << "\n";
	}
	if (a.defense != 0.0f)
	{
		std::cout << "Defense: "
			<< GetPrefixSign(a.defense)
			<< a.defense << "\n";
	}

	std::cout << "Weight: +"
		<< static_cast<int>(myItemType->GetAttributes().weight)
		<< "kg\n";
}

void Item::PrintItemOnPickup() const
{
	std::cout << GetColorCode(GetColorFromRarity(myItemType->GetAttributes().rarity), true)
		<< "\n<------ " << RarityToString(myItemType->GetAttributes().rarity) << " ------>"
		<< GetColorCode(GetColorFromRarity(myItemType->GetAttributes().rarity), false)
		<< "\n"
		<< "         [" << myItemType->GetAttributes().name << "]" << "\n";

	PrintItemAttributes();

	std::cout << "\n";
}

void Item::PrintItemOnDisplay() const
{
	PrintItemName();
	std::cout << "\n";
	PrintItemAttributes();
}

void Item::PrintItemName() const
{
	std::cout << GetColorCode(GetColorFromRarity(myItemType->GetAttributes().rarity), true)
		<< "[" << myItemType->GetAttributes().name << "]"
		<< GetColorCode(GetColorFromRarity(myItemType->GetAttributes().rarity), false);
}
