#include "Spell.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

Spell::Spell(SpellType* aSpellType, int aId)
	: myId(aId),
	  myState{false, DEFAULT_ON_HIT_COUNT},
	  mySpellType(aSpellType)
{
}

void Spell::UpdateOnHitCount()
{
	if (myState.isActive)
	{
		myState.hitCount--;
	}
}

void Spell::ActivateSpell()
{
	myState.isActive = true;
}

bool Spell::GetSpellFinished() const
{
	if (myState.hitCount < 0)
	{
		return true;
	}
	return false;
}

void Spell::PrintSpellAttributes() const
{
	// Print non-zero attributes
	const Attributes& a = GetAttributes();
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
		<< myState.hitCount
		<< "/"
		<< DEFAULT_ON_HIT_COUNT << "\n";
}

void Spell::PrintSpellOnPickup() const
{
	std::cout << GetColorCode(GetColorFromRarity(GetSpellAttributes().rarity), true)
		<< "\n<------ " << RarityToString(GetSpellAttributes().rarity) << " ------>"
		<< GetColorCode(GetColorFromRarity(GetSpellAttributes().rarity), false)
		<< "\n"
		<< "         {" << GetSpellAttributes().name << "}" << "\n";

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
	std::cout << GetColorCode(GetColorFromRarity(GetSpellAttributes().rarity), true)
		<< "{" << GetSpellAttributes().name << "}"
		<< GetColorCode(GetColorFromRarity(GetSpellAttributes().rarity), false);
}
