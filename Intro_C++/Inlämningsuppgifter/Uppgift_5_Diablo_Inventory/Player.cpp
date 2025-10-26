#include "Player.h"
#include "WorldMap.h"
#include "Utils.h"
#include "Cheats.h"
#include "Item.h"
#include <iostream>

#include "ConsoleUI.h"

Player::Player(WorldMap& aWorldMap) : myWorldMap(aWorldMap), myName("(-)"), myRoomId(0),
                                      myIsDead(false), myPos{0, 0}
{
    myAttributes.strength = DEFAULT_BASE_ATTRIBUTE;
    myAttributes.agility = DEFAULT_BASE_ATTRIBUTE;
    myAttributes.endurance = DEFAULT_BASE_ATTRIBUTE;

    myAttributes.currentHealth = GetMaxHealth(myAttributes);
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
        << "" << dmg << " dmg to you"
        << " [" << blockedDmg << " blocked damage]\n";

    myAttributes.currentHealth -= dmgFloat;
    mySpellBook.UpdateSpellsOnHitCount();

    if (myAttributes.currentHealth <= HEALTH_ZERO)
    {
        myAttributes.currentHealth = HEALTH_ZERO;
        myIsDead = true;
        std::cout << "\n" << "You died!";
        std::cout << "\n" << "Quitting game...\n";
        ConsoleUI::Pause();
    }
}

float Player::GetDamage(const Attributes& aAttributes) const
{
    if (Cheats::GetCheats().oneShot)
    {
        return aAttributes.strength * aAttributes.agility * CHEATS_ONESHOT_MULTI;
    }
    return aAttributes.strength * aAttributes.agility;
}

float Player::GetMaxHealth(const Attributes& aAttributes) const
{
    return (aAttributes.endurance * ATTRI_GET_HEALTH_ENDURANCE_MULTI) +
        (aAttributes.strength * ATTRI_GET_HEALTH_STRENGTH_MULTI) +
        (aAttributes.agility * ATTRI_GET_HEALTH_AGILITY_MULTI);
}

float Player::GetCarryCapacity(const Attributes& aAttributes) const
{
    return aAttributes.strength + (aAttributes.agility / ATTRI_GET_CARRY_AGILITY_DIV);
}

float Player::GetDefense(const Attributes& aAttributes) const
{
    return aAttributes.endurance + aAttributes.agility;
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
        GetMaxHealth(myAttributes),
        myAttributes.currentHealth,
        GetCarryCapacity(myAttributes),
        GetDamage(myAttributes),
        GetDefense(myAttributes),
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
