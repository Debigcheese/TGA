#include "SpellFactory.h"

SpellFactory::SpellFactory()
	: myTypes{
		{
			SpellKey::MagicMissile, Rarity::Bronze, "Magic Missile",
			{
				0.0f, 5.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				25.0f, 0.0f
			}
		},
		{
			SpellKey::Fireball, Rarity::Silver, "Fireball",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				100.0f, 0.0f
			}
		},
		{
			SpellKey::MeteorStrike, Rarity::Gold, "Meteor Strike",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				175.0f, 0.0f
			}
		},
		{
			SpellKey::ChainLightning, Rarity::Legendary, "Chain Lightning",
			{
				0.0f, 5.0f, 0.0f,
				10.0f, 0.0f, 0.0f,
				250.0f, 0.0f
			}
		},
		{
			SpellKey::FrostBolt, Rarity::Silver, "Frost Bolt",
			{
				0.0f, 0.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				60.0f, 10.0f
			}
		},
		{
			SpellKey::Blizzard, Rarity::Gold, "Blizzard",
			{
				0.0f, 0.0f, 10.0f,
				20.0f, 0.0f, 0.0f,
				120.0f, 15.0f
			}
		},
		{
			SpellKey::PoisonDart, Rarity::Bronze, "Poison Dart",
			{
				0.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				20.0f, -5.0f
			}
		},
		{
			SpellKey::AcidSpray, Rarity::Silver, "Acid Spray",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				45.0f, -15.0f
			}
		},
		{
			SpellKey::TimeWarp, Rarity::Legendary, "Time Warp",
			{
				10.0f, 60.0f, 10.0f,
				15.0f, 0.0f, 0.0f,
				0.0f, 0.0f
			}
		},
		{
			SpellKey::Earthquake, Rarity::Gold, "Earthquake",
			{
				15.0f, 0.0f, 20.0f,
				0.0f, 0.0f, 0.0f,
				90.0f, 0.0f
			}
		},
		{
			SpellKey::StoneSkin, Rarity::Silver, "Stone Skin",
			{
				0.0f, 0.0f, 30.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 60.0f
			}
		},
		{
			SpellKey::Shockwave, Rarity::Bronze, "Shockwave",
			{
				5.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				35.0f, 0.0f
			}
		},
		{
			SpellKey::PhoenixFlame, Rarity::Gold, "Phoenix Flame",
			{
				0.0f, 0.0f, 0.0f,
				50.0f, 0.0f, 0.0f,
				140.0f, 0.0f
			}
		},
		{
			SpellKey::WindSlash, Rarity::Silver, "Wind Slash",
			{
				0.0f, 15.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				55.0f, 0.0f
			}
		},
		{
			SpellKey::Hurricane, Rarity::Legendary, "Hurricane",
			{
				0.0f, 40.0f, 20.0f,
				30.0f, 0.0f, 0.0f,
				180.0f, 0.0f
			}
		},
		{
			SpellKey::HealingLight, Rarity::Bronze, "Healing Light",
			{
				0.0f, 0.0f, 0.0f,
				40.0f, 0.0f, 0.0f,
				0.0f, 0.0f
			}
		},
		{
			SpellKey::DivineShield, Rarity::Silver, "Divine Shield",
			{
				0.0f, 0.0f, 15.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 80.0f
			}
		},
		{
			SpellKey::ArcaneBlast, Rarity::Gold, "Arcane Blast",
			{
				0.0f, 20.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				160.0f, 0.0f
			}
		},
		{
			SpellKey::BlackHole, Rarity::Legendary, "Black Hole",
			{
				0.0f, 0.0f, -20.0f,
				0.0f, 0.0f, 0.0f,
				300.0f, 0.0f
			}
		},
		{
			SpellKey::NecroticGrasp, Rarity::Gold, "Necrotic Grasp",
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				200.0f, 0.0f
			}
		}
	}
{
}

SpellFactory& SpellFactory::GetFactory()
{
	static SpellFactory instance;
	return instance;
}

Spell SpellFactory::Create(const SpellKey aKey)
{
	return Spell(myTypes[static_cast<int>(aKey)]);
}

std::vector<SpellKey> SpellFactory::GetSpellKeysFromRarities(const std::vector<Rarity>& aRarities) const
{
	std::vector<SpellKey> keysWithRarity;
	for (const auto& a : myTypes)
	{
		for (const auto& r : aRarities)
		{
			if (a.rarity == r)
			{
				keysWithRarity.push_back(a.key);
			}
		}
	}
	return keysWithRarity;
}

std::vector<Spell> SpellFactory::CreateSpellsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const
{
	std::vector<SpellKey> spellIdPool = GetSpellKeysFromRarities(Utils::GetRaritiesFromMax(aRarity));
	// random item pool with rarities up to "aRarity"

	if (spellIdPool.empty() || aMaxAmount <= 0 || aMaxAmount < aMinAmount)
	{
		return {};
	}

	const int RANDOM_SIZE = Utils::GenerateRandomNumber(aMinAmount, aMaxAmount); // amount of items to get

	std::vector<Spell> spellsInRoom = {};
	spellsInRoom.reserve(RANDOM_SIZE);

	for (int i = 0; i < RANDOM_SIZE; ++i)
	{
		//generate random index to pick from my itemIdPool
		int randomIndex = Utils::GenerateRandomNumber(0, static_cast<int>(spellIdPool.size() - 1));
		SpellKey chosenKey = spellIdPool[randomIndex];
		spellsInRoom.emplace_back(SpellFactory::GetFactory().Create(chosenKey));

		spellIdPool[randomIndex] = spellIdPool.back();
		spellIdPool.pop_back();
	}
	return spellsInRoom;
}
