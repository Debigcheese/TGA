#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include <vector>

#include "Spell.h"

namespace SpellDB
{
	const SpellAttributes SpellDef[] = {
		{
			0, Rarity::Bronze, "Magic Missile",
			{
				0.0f, 5.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				25.0f, 0.0f
			}
		},
		{
			1, Rarity::Silver, "Fireball",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				100.0f, 0.0f
			}
		},
		{
			2, Rarity::Gold, "Meteor Strike",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				175.0f, 0.0f
			}
		},
		{
			3, Rarity::Legendary, "Chain Lightning",
			{
				0.0f, 5.0f, 0.0f,
				10.0f, 0.0f, 0.0f,
				250.0f, 0.0f
			}
		},
		{
			4, Rarity::Silver, "Frost Bolt",
			{
				0.0f, 0.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				60.0f, 10.0f
			}
		},
		{
			5, Rarity::Gold, "Blizzard",
			{
				0.0f, 0.0f, 10.0f,
				20.0f, 0.0f, 0.0f,
				120.0f, 15.0f
			}
		},
		{
			6, Rarity::Bronze, "Poison Dart",
			{
				0.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				20.0f, -5.0f
			}
		},
		{
			7, Rarity::Silver, "Acid Spray",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				45.0f, -15.0f
			}
		},
		{
			8, Rarity::Legendary, "Time Warp",
			{
				10.0f, 60.0f, 10.0f,
				15.0f, 0.0f, 0.0f,
				0.0f, 0.0f
			}
		},
		{
			9, Rarity::Gold, "Earthquake",
			{
				15.0f, 0.0f, 20.0f,
				0.0f, 0.0f, 0.0f,
				90.0f, 0.0f
			}
		},
		{
			10, Rarity::Silver, "Stone Skin",
			{
				0.0f, 0.0f, 30.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 60.0f
			}
		},
		{
			11, Rarity::Bronze, "Shockwave",
			{
				5.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				35.0f, 0.0f
			}
		},
		{
			12, Rarity::Gold, "Phoenix Flame",
			{
				0.0f, 0.0f, 0.0f,
				50.0f, 0.0f, 0.0f,
				140.0f, 0.0f
			}
		},
		{
			13, Rarity::Silver, "Wind Slash",
			{
				0.0f, 15.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				55.0f, 0.0f
			}
		},
		{
			14, Rarity::Legendary, "Hurricane",
			{
				0.0f, 40.0f, 20.0f,
				30.0f, 0.0f, 0.0f,
				180.0f, 0.0f
			}
		},
		{
			15, Rarity::Bronze, "Healing Light",
			{
				0.0f, 0.0f, 0.0f,
				40.0f, 0.0f, 0.0f,
				0.0f, 0.0f
			}
		},
		{
			16, Rarity::Silver, "Divine Shield",
			{
				0.0f, 0.0f, 15.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 80.0f
			}
		},
		{
			17, Rarity::Gold, "Arcane Blast",
			{
				0.0f, 20.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				160.0f, 0.0f
			}
		},
		{
			18, Rarity::Legendary, "Black Hole",
			{
				0.0f, 0.0f, -20.0f,
				0.0f, 0.0f, 0.0f,
				300.0f, 0.0f
			}
		},
		{
			19, Rarity::Gold, "Necrotic Grasp",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				200.0f, 0.0f
			}
		},

	};

	const SpellAttributes& GetDef(int aId);
	int GetItemCount();
	std::vector<int> GetIdsFromRarities(const std::vector<Rarity>& aRarities);
}
