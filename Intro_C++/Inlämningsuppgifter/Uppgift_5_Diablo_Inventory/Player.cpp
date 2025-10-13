#include "Player.h"
#include "WorldMap.h"
#include "Utils.h"
#include "Cheats.h"
#include "Item.h"

#include <iostream>

#include "ConsoleUI.h"

Player::Player(WorldMap& aWorldMap) : myWorldMap(aWorldMap), myRoomId(0), myIsDead(false),
                                      myName("(-)"), myPos{0, 0}
{
	myAttributes.strength = DEFAULT_BASE_ATTRIBUTE;
	myAttributes.agility = DEFAULT_BASE_ATTRIBUTE;
	myAttributes.endurance = DEFAULT_BASE_ATTRIBUTE;

	myAttributes.currentHealth = GetMaxHealth();
}

void Player::TakeDamage(const float aDamage, const std::string aEnemyName)
{
	if (Cheats::GetCheats().invincible)
	{
		return;
	}

	const float dmgFloat = aDamage / GetDefenseMultiplier();
	const int dmg = static_cast<int>(dmgFloat);
	const int blockedDmg = static_cast<int>(aDamage) - dmg;

	std::cout << aEnemyName << " dealt "
		<< "" << static_cast<int>(dmg) << " dmg to you"
		<< " [" << blockedDmg << " blocked damage]\n";

	myAttributes.currentHealth -= dmgFloat;
	mySpellBook.UpdateSpellsOnHitCount();

	if (myAttributes.currentHealth <= HEALTH_ZERO)
	{
		myAttributes.currentHealth = HEALTH_ZERO;
		myIsDead = true;
		std::cout << "\n" << "You died!";
		std::cout << "\n" << "Quitting game...\n";
		system("pause");
	}
}

float Player::GetDamage() const
{
	if (Cheats::GetCheats().oneShot)
	{
		return myAttributes.strength * myAttributes.agility * CHEATS_ONESHOT_MULTI;
	}
	return myAttributes.strength * myAttributes.agility;
}

float Player::GetMaxHealth() const
{
	return (myAttributes.endurance * ATTRI_GET_HEALTH_ENDURANCE_MULTI) +
		(myAttributes.strength * ATTRI_GET_HEALTH_STRENGTH_MULTI) +
		(myAttributes.agility * ATTRI_GET_HEALTH_AGILITY_MULTI);
}

float Player::GetCarryCapacity() const
{
	return myAttributes.strength + (myAttributes.agility / ATTRI_GET_CARRY_AGILITY_DIV);
}

float Player::GetDefense() const
{
	return myAttributes.endurance + myAttributes.agility;
}

float Player::GetDefenseMultiplier() const
{
	return (DEFENSE_BASE_MULTI + (GetAttributes().defense / DEFENSE_SCALING_FACTOR)); // (defense {20-198} /200) 
}

Attributes Player::GetBaseAttributes() const
{
	return {
		myAttributes.strength,
		myAttributes.agility,
		myAttributes.endurance,
		GetMaxHealth(),
		myAttributes.currentHealth,
		GetCarryCapacity(),
		GetDamage(),
		GetDefense(),
	};
}

Attributes Player::GetBuffedAttributes() const
{
	Attributes buffedAttributes = {};
	buffedAttributes += GetEquipment().GetAttributes();
	buffedAttributes += GetSpellBook().GetAttributes();
	return buffedAttributes;
}

Attributes Player::GetAttributes() const
{
	return {

		GetBaseAttributes().strength + GetBuffedAttributes().strength,
		GetBaseAttributes().agility + GetBuffedAttributes().agility,
		GetBaseAttributes().endurance + GetBuffedAttributes().endurance,
		GetBaseAttributes().maxHealth + GetBuffedAttributes().maxHealth,
		GetBaseAttributes().currentHealth + GetBuffedAttributes().currentHealth,
		GetBaseAttributes().carryCapacity + GetBuffedAttributes().carryCapacity,
		GetBaseAttributes().damage + GetBuffedAttributes().damage,
		GetBaseAttributes().defense + GetBuffedAttributes().defense
	};
}

bool Player::CanPickupItem(const Item& aItem) const
{
	if (GetAttributes().carryCapacity >= myInventory.GetInventoryWeight() + aItem.GetItemAttributes().weight)
	{
		return true;
	}
	return false;
}



