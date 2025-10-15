#include "Item.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

Item::Item(ItemType* aItemType, int aId)
    : myItemType(aItemType), myId(aId)
{
}

void Item::PrintItemAttributes() const
{
    // Print non-zero attributes
    const Attributes& a = GetAttributes();
    if (a.strength != 0.0f)
    {
        std::cout << "Strength: "
            << GetPrefixSign(a.strength)
            << static_cast<int>(a.strength) << "\n";
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
        << static_cast<int>(GetItemAttributes().weight)
        << "kg\n";
}

void Item::PrintItemOnDisplay() const
{
    PrintItemName();
    std::cout << "\n";
    PrintItemAttributes();
}

void Item::PrintItemName() const
{
    std::cout << GetColorCode(GetColorFromRarity(GetItemAttributes().rarity), true)
        << "[" << GetItemAttributes().name << "]"
        << GetColorCode(GetColorFromRarity(GetItemAttributes().rarity), false);
}
