#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include <vector>

namespace ItemDB
{
	const ItemAttributes ITEM_DEF[] = {
		{
			0, ItemType::Weapon, Rarity::Bronze, "Eclipse", 1.0f,
			{
				10.0f, 5.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				40.0f, 0.0f
			}
		},
		{
			1, ItemType::Weapon, Rarity::Legendary, "GodSword", 3.0f,
			{
				15.0f, 10.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				100.0f, 0.0f
			}
		},
		{
			2, ItemType::Armor, Rarity::Bronze, "Aegis", 1.0f,
			{
				0.0f, -5.0f, 20.0f,
				0.0f, 0.0f, 2.0f,
				0.0f, 50.0f
			}
		},
		{
			4, ItemType::Armor, Rarity::Gold, "Backpack", 0.0f,
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 3.0f,
				0.0f, 0.0f
			}
		},
		{
			5, ItemType::Weapon, Rarity::Silver, "Storm Breaker", 2.0f,
			{
				12.0f, 5.0f, 0.0f,
				0.0f, 0, 0.0f,
				55.0f, 0.0f
			}
		},
		{
			6, ItemType::Armor, Rarity::Gold, "Dragon Scale", 3.0f,
			{
				5.0f, 0.0f, 50.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 150.0f
			}
		},
		{
			8, ItemType::Weapon, Rarity::Bronze, "Rusty Dagger", 1.0f,
			{
				0.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				15.0f, 0.0f
			}
		},
		{
			9, ItemType::Armor, Rarity::Silver, "Knight Helm", 1.0f,
			{
				0.0f, 0.0f, 20.0f,
				0.0f, 0.0f, 2.0f,
				0.0f, 25.0f
			}
		},
		{
			11, ItemType::Weapon, Rarity::Gold, "Blood Fang", 2.0f,
			{
				8.0f, 8.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				90.0f, -10.0f
			}
		},
		{
			12, ItemType::Armor, Rarity::Legendary, "Celestial Shield", 1.0f,
			{
				0.0f, 0.0f, 40.0f,
				0.0f, 0.0f, 4.0f,
				0.0f, 100.0f
			}
		},
		{
			13, ItemType::Weapon, Rarity::Silver, "War Axe", 2.0f,
			{
				15.0f, -2.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				60.0f, 0.0f
			}
		},
		{
			14, ItemType::Armor, Rarity::Bronze, "Leather Boots", 1.0f,
			{
				0.0f, 3.0f, 5.0f,
				0.0f, 0.0f, 2.0f,
				0.0f, 10.0f
			}
		},
		{
			16, ItemType::Weapon, Rarity::Legendary, "Void Reaver", 2.0f,
			{
				15.0f, 15.0f, -10.0f,
				0.0f, 0.0f, 0.0f,
				150.0f, 0.0f
			}
		},
		{
			17, ItemType::Armor, Rarity::Silver, "Iron Chestplate", 2.0f,
			{
				-5.0f, 0.0f, 20.0f,
				0.0f, 0.0f, 1.0f,
				0.0f, 80.0f
			}
		},
		{
			18, ItemType::Weapon, Rarity::Bronze, "Training Sword", 1.0f,
			{
				5.0f, 2.0f, 2.0f,
				0.0f, 0.0f, 0.0f,
				10.0f, 0.0f
			}
		},
	};

	const ItemAttributes& GetDef(int aId);
	int GetItemCount();
	std::vector<int> GetIdsFromRarities(const std::vector<Rarity>& aRarities);
}
