#include "Item.h"
#include "ItemDB.h"
#include "Player.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

Item::Item(int aId) :
	myAttributes{
		ItemDB::GetDef(aId).id,
		ItemDB::GetDef(aId).type,
		ItemDB::GetDef(aId).rarity,
		ItemDB::GetDef(aId).name,
		ItemDB::GetDef(aId).weight,
		ItemDB::GetDef(aId).attributes
	}
{
}

const char* Item::GetName() const
{
	return myAttributes.name;
}

float Item::GetWeight() const
{
	return myAttributes.weight;
}

ItemAttributes Item::GetAttributes() const
{
	return myAttributes;
}

void Item::SetId(int aNewId)
{
	myAttributes.id = aNewId;
}

void Item::PrintItemOnPickup() const
{
	std::cout << GetColorCode(GetColorFromRarity(myAttributes.rarity), true)
		<< "\n<------ " << RarityToString(myAttributes.rarity) << " ------>"
		<< GetColorCode(GetColorFromRarity(myAttributes.rarity), false)
		<< "\n"
		<< "[" << myAttributes.name << "]" << "\n";

	// Print non-zero attributes
	const Attributes& a = myAttributes.attributes;
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

	std::cout << "\n";
}

void Item::PrintItemAttributes() const
{
	std::cout << "";
}
