#include "Spell.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

Spell::Spell(const SpellAttributes& aAttributes)
	: myOnHitCount(DEFAULT_ON_HIT_COUNT),
	  myAttributes(aAttributes)
{
}

void Spell::UpdateOnHitCount()
{
	myOnHitCount--;
}

const char* Spell::GetName() const
{
	return myAttributes.name;
}

SpellAttributes Spell::GetAttributes() const
{
	return myAttributes;
}

bool Spell::GetSpellFinished() const
{
	if (myOnHitCount < 0)
	{
		return true;
	}
	return false;
}

void Spell::PrintSpellAttributes() const
{
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
	std::cout << "Hit Count: "
		<< myOnHitCount
		<< "/"
		<< DEFAULT_ON_HIT_COUNT << "\n";
}

void Spell::PrintSpellOnPickup() const
{
	std::cout << GetColorCode(GetColorFromRarity(myAttributes.rarity), true)
		<< "\n<------ " << RarityToString(myAttributes.rarity) << " ------>"
		<< GetColorCode(GetColorFromRarity(myAttributes.rarity), false)
		<< "\n"
		<< "         {" << myAttributes.name << "}" << "\n";

	PrintSpellAttributes();

	std::cout << "\n";
}

void Spell::PrintSpellOnDisplay() const
{
	PrintSpellName();
	std::cout << "\n";
	PrintSpellAttributes();
}

void Spell::PrintSpellName() const
{
	std::cout << GetColorCode(GetColorFromRarity(myAttributes.rarity), true)
		<< "{" << myAttributes.name << "}"
		<< GetColorCode(GetColorFromRarity(myAttributes.rarity), false);
}
