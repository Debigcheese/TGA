#include "ItemFactory.h"
#include "Utils.h"

ItemFactory::ItemFactory() : myTypes({})

{
	InitFactory();
}

ItemFactory& ItemFactory::GetFactory()
{
	static ItemFactory instance;
	return instance;
}

Item ItemFactory::Create(ItemKey aKey)
{
	if (aKey <= ItemKey::None || aKey >= ItemKey::Count || static_cast<int>(aKey) >= static_cast<int>(myTypes.size()))
	{
		aKey = static_cast<ItemKey>(Utils::GenerateRandomNumber
			(static_cast<int>(ItemKey::None) + 1,
			 static_cast<int>(myTypes.size()) - 1));
	}
	ItemType& type = myTypes[static_cast<int>(aKey)];
	return {(&type)}; // returns Item address with pointer to type
}

void ItemFactory::InitFactory()
{
	myTypes.resize(static_cast<int>(ItemKey::Count));

	myTypes[static_cast<int>(ItemKey::Eclipse)].SetAttributes({
		ItemKey::Eclipse, EquipmentType::Hand, Rarity::Bronze, "Eclipse", 1.0f,
		{
			10.0f, 5.0f, 5.0f,
			0.0f, 0.0f, 0.0f,
			40.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::GodSword)].SetAttributes({
		ItemKey::GodSword, EquipmentType::Hand, Rarity::Legendary, "GodSword", 3.0f,
		{
			16.0f, 9.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			100.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::Aegis)].SetAttributes({
		ItemKey::Aegis, EquipmentType::Body, Rarity::Bronze, "Aegis", 1.0f,
		{
			0.0f, -4.0f, 18.0f,
			0.0f, 0.0f, 2.0f,
			0.0f, 50.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::Backpack)].SetAttributes({
		ItemKey::Backpack, EquipmentType::Amulet, Rarity::Gold, "Backpack", 0.0f,
		{
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 4.0f,
			0.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::StormBreaker)].SetAttributes({
		ItemKey::StormBreaker, EquipmentType::Hand, Rarity::Silver, "Storm Breaker", 2.0f,
		{
			12.0f, 5.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			55.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::DragonScale)].SetAttributes({
		ItemKey::DragonScale, EquipmentType::Body, Rarity::Gold, "Dragon Scale", 3.0f,
		{
			5.0f, 0.0f, 45.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 140.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::RustyDagger)].SetAttributes({
		ItemKey::RustyDagger, EquipmentType::Hand, Rarity::Bronze, "Rusty Dagger", 1.0f,
		{
			0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			14.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::KnightHelm)].SetAttributes({
		ItemKey::KnightHelm, EquipmentType::Head, Rarity::Silver, "Knight Helm", 1.0f,
		{
			0.0f, 0.0f, 18.0f,
			0.0f, 0.0f, 2.0f,
			0.0f, 24.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::BloodFang)].SetAttributes({
		ItemKey::BloodFang, EquipmentType::Hand, Rarity::Gold, "Blood Fang", 2.0f,
		{
			8.0f, 8.0f, -2.0f,
			0.0f, 0.0f, 0.0f,
			88.0f, -8.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::CelestialShield)].SetAttributes({
		ItemKey::CelestialShield, EquipmentType::Body, Rarity::Legendary, "Celestial Shield", 2.0f,
		{
			0.0f, 0.0f, 25.0f,
			0.0f, 0.0f, 4.0f,
			0.0f, 95.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::WarAxe)].SetAttributes({
		ItemKey::WarAxe, EquipmentType::Hand, Rarity::Silver, "War Axe", 2.0f,
		{
			15.0f, -2.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			60.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::LeatherBoots)].SetAttributes({
		ItemKey::LeatherBoots, EquipmentType::Feet, Rarity::Bronze, "Leather Boots", 1.0f,
		{
			0.0f, 3.0f, 4.0f,
			0.0f, 0.0f, 2.0f,
			0.0f, 10.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::VoidReaver)].SetAttributes({
		ItemKey::VoidReaver, EquipmentType::Hand, Rarity::Legendary, "Void Reaver", 3.0f,
		{
			15.0f, 15.0f, -8.0f,
			0.0f, 0.0f, 0.0f,
			150.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::IronChestplate)].SetAttributes({
		ItemKey::IronChestplate, EquipmentType::Body, Rarity::Silver, "Iron Chestplate", 2.0f,
		{
			-4.0f, 0.0f, 20.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 78.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::TrainingSword)].SetAttributes({
		ItemKey::TrainingSword, EquipmentType::Hand, Rarity::Bronze, "Training Sword", 1.0f,
		{
			5.0f, 2.0f, 2.0f,
			0.0f, 0.0f, 0.0f,
			10.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::HunterGloves)].SetAttributes({
		ItemKey::HunterGloves, EquipmentType::Hand, Rarity::Bronze, "Hunter Gloves", 0.0f,
		{
			0.0f, 4.0f, 2.0f,
			0.0f, 0.0f, 1.0f,
			5.0f, 8.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::SwiftGreaves)].SetAttributes({
		ItemKey::SwiftGreaves, EquipmentType::Legs, Rarity::Silver, "Swift Greaves", 1.0f,
		{
			0.0f, 6.0f, 6.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 16.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::TitanGauntlets)].SetAttributes({
		ItemKey::TitanGauntlets, EquipmentType::Hand, Rarity::Gold, "Titan Gauntlets", 1.0f,
		{
			6.0f, -2.0f, 10.0f,
			0.0f, 0.0f, 1.0f,
			12.0f, 28.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::RangerHood)].SetAttributes({
		ItemKey::RangerHood, EquipmentType::Head, Rarity::Bronze, "Ranger Hood", 1.0f,
		{
			0.0f, 5.0f, 3.0f,
			0.0f, 0.0f, 0.0f,
			4.0f, 8.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::CrusaderPlate)].SetAttributes({
		ItemKey::CrusaderPlate, EquipmentType::Body, Rarity::Gold, "Crusader Plate", 3.0f,
		{
			4.0f, -2.0f, 30.0f,
			0.0f, 0.0f, 0.0f,
			6.0f, 110.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::ShadowstepBoots)].SetAttributes({
		ItemKey::ShadowstepBoots, EquipmentType::Feet, Rarity::Silver, "Shadowstep Boots", 1.0f,
		{
			0.0f, 8.0f, 2.0f,
			0.0f, 0.0f, 2.0f,
			8.0f, 6.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::BerserkerAmulet)].SetAttributes({
		ItemKey::BerserkerAmulet, EquipmentType::Amulet, Rarity::Gold, "Berserker Amulet", 0.0f,
		{
			10.0f, 0.0f, -6.0f,
			0.0f, 0.0f, 0.0f,
			22.0f, -10.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::QuartzAmulet)].SetAttributes({
		ItemKey::QuartzAmulet, EquipmentType::Amulet, Rarity::Bronze, "Quartz Amulet", 0.0f,
		{
			0.0f, 2.0f, 2.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 6.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::Frostbrand)].SetAttributes({
		ItemKey::Frostbrand, EquipmentType::Hand, Rarity::Silver, "Frostbrand", 2.0f,
		{
			9.0f, 4.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			62.0f, 6.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::Sunpiercer)].SetAttributes({
		ItemKey::Sunpiercer, EquipmentType::Hand, Rarity::Gold, "Sunpiercer", 2.0f,
		{
			7.0f, 11.0f, -2.0f,
			0.0f, 0.0f, 0.0f,
			85.0f, 4.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::ThunderMaul)].SetAttributes({
		ItemKey::ThunderMaul, EquipmentType::Hand, Rarity::Legendary, "Thunder Maul", 3.0f,
		{
			20.0f, -6.0f, 6.0f,
			0.0f, 0.0f, 0.0f,
			130.0f, 10.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::SerpentLeggings)].SetAttributes({
		ItemKey::SerpentLeggings, EquipmentType::Legs, Rarity::Bronze, "Serpent Leggings", 1.0f,
		{
			0.0f, 4.0f, 6.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 12.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::WardenGloves)].SetAttributes({
		ItemKey::WardenGloves, EquipmentType::Hand, Rarity::Silver, "Warden Gloves", 1.0f,
		{
			3.0f, 0.0f, 8.0f,
			0.0f, 0.0f, 1.0f,
			6.0f, 18.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::NightwatchHelm)].SetAttributes({
		ItemKey::NightwatchHelm, EquipmentType::Head, Rarity::Gold, "Nightwatch Helm", 1.0f,
		{
			0.0f, 6.0f, 10.0f,
			0.0f, 0.0f, 0.0f,
			8.0f, 26.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::OakheartChest)].SetAttributes({
		ItemKey::OakheartChest, EquipmentType::Body, Rarity::Bronze, "Oakheart Chest", 2.0f,
		{
			2.0f, -2.0f, 16.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 22.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::PilgrimBoots)].SetAttributes({
		ItemKey::PilgrimBoots, EquipmentType::Feet, Rarity::Silver, "Pilgrim Boots", 1.0f,
		{
			0.0f, 5.0f, 3.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 9.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::SteelKneeguards)].SetAttributes({
		ItemKey::SteelKneeguards, EquipmentType::Legs, Rarity::Silver, "Steel Kneeguards", 1.0f,
		{
			-1.0f, 0.0f, 14.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 20.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::FalconAmulet)].SetAttributes({
		ItemKey::FalconAmulet, EquipmentType::Amulet, Rarity::Silver, "Falcon Amulet", 0.0f,
		{
			2.0f, 6.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			10.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::VanguardHelm)].SetAttributes({
		ItemKey::VanguardHelm, EquipmentType::Head, Rarity::Legendary, "Vanguard Helm", 2.0f,
		{
			4.0f, 4.0f, 18.0f,
			0.0f, 0.0f, 0.0f,
			12.0f, 40.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::ForgemasterGloves)].SetAttributes({
		ItemKey::ForgemasterGloves, EquipmentType::Hand, Rarity::Gold, "Forgemaster Gloves", 1.0f,
		{
			6.0f, 2.0f, 8.0f,
			0.0f, 0.0f, 0.0f,
			14.0f, 20.0f
		}
	});
}

std::vector<ItemKey> ItemFactory::GetItemKeysFromRarities(const std::vector<Rarity>& aRarities) const
{
	std::vector<ItemKey> keysWithRarity;
	for (const auto& a : myTypes)
	{
		for (const auto& r : aRarities)
		{
			if (a.GetItemAttributes().rarity == r)
			{
				keysWithRarity.push_back(a.GetItemAttributes().key);
			}
		}
	}
	return keysWithRarity;
}

std::vector<Item> ItemFactory::CreateItemsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const
{
	std::vector<ItemKey> itemKeyPool = GetItemKeysFromRarities(Utils::GetRaritiesFromMax(aRarity));

	// random item pool with rarities up to "aRarity"

	if (itemKeyPool.empty() || aMaxAmount <= 0 || aMaxAmount < aMinAmount)
	{
		return {};
	}

	const int RANDOM_SIZE = Utils::GenerateRandomNumber(aMinAmount, aMaxAmount); // amount of items to get

	std::vector<Item> itemsInRoom = {};
	itemsInRoom.reserve(RANDOM_SIZE);

	for (int i = 0; i < RANDOM_SIZE; ++i)
	{
		//generate random index to pick from my itemIdPool
		int randomIndex = Utils::GenerateRandomNumber(0, static_cast<int>(itemKeyPool.size() - 1));
		ItemKey chosenKey = itemKeyPool[randomIndex];
		itemsInRoom.emplace_back(ItemFactory::GetFactory().Create(chosenKey));

		itemKeyPool[randomIndex] = itemKeyPool.back();
		itemKeyPool.pop_back();
	}
	return itemsInRoom;
}
