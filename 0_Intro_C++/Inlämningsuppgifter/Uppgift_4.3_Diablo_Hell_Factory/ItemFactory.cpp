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
		ItemKey::Eclipse, ItemTypes::Weapon, Rarity::Bronze, "Eclipse", 1.0f,
		{
			10.0f, 5.0f, 5.0f,
			0.0f, 0.0f, 0.0f,
			40.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::GodSword)].SetAttributes({
		ItemKey::GodSword, ItemTypes::Weapon, Rarity::Legendary, "GodSword", 3.0f,
		{
			15.0f, 10.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			100.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::Aegis)].SetAttributes({
		ItemKey::Aegis, ItemTypes::Armor, Rarity::Bronze, "Aegis", 1.0f,
		{
			0.0f, -5.0f, 20.0f,
			0.0f, 0.0f, 2.0f,
			0.0f, 50.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::Backpack)].SetAttributes({
		ItemKey::Backpack, ItemTypes::Armor, Rarity::Gold, "Backpack", 0.0f,
		{
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 3.0f,
			0.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::StormBreaker)].SetAttributes({
		ItemKey::StormBreaker, ItemTypes::Weapon, Rarity::Silver, "Storm Breaker", 2.0f,
		{
			12.0f, 5.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			55.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::DragonScale)].SetAttributes({
		ItemKey::DragonScale, ItemTypes::Armor, Rarity::Gold, "Dragon Scale", 3.0f,
		{
			5.0f, 0.0f, 50.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 150.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::RustyDagger)].SetAttributes({
		ItemKey::RustyDagger, ItemTypes::Weapon, Rarity::Bronze, "Rusty Dagger", 1.0f,
		{
			0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			15.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::KnightHelm)].SetAttributes({
		ItemKey::KnightHelm, ItemTypes::Armor, Rarity::Silver, "Knight Helm", 1.0f,
		{
			0.0f, 0.0f, 20.0f,
			0.0f, 0.0f, 2.0f,
			0.0f, 25.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::BloodFang)].SetAttributes({
		ItemKey::BloodFang, ItemTypes::Weapon, Rarity::Gold, "Blood Fang", 2.0f,
		{
			8.0f, 8.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			90.0f, -10.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::CelestialShield)].SetAttributes({
		ItemKey::CelestialShield, ItemTypes::Armor, Rarity::Legendary, "Celestial Shield", 1.0f,
		{
			0.0f, 0.0f, 40.0f,
			0.0f, 0.0f, 4.0f,
			0.0f, 100.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::WarAxe)].SetAttributes({
		ItemKey::WarAxe, ItemTypes::Weapon, Rarity::Silver, "War Axe", 2.0f,
		{
			15.0f, -2.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			60.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::LeatherBoots)].SetAttributes({
		ItemKey::LeatherBoots, ItemTypes::Armor, Rarity::Bronze, "Leather Boots", 1.0f,
		{
			0.0f, 3.0f, 5.0f,
			0.0f, 0.0f, 2.0f,
			0.0f, 10.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::VoidReaver)].SetAttributes({
		ItemKey::VoidReaver, ItemTypes::Weapon, Rarity::Legendary, "Void Reaver", 2.0f,
		{
			15.0f, 15.0f, -10.0f,
			0.0f, 0.0f, 0.0f,
			150.0f, 0.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::IronChestplate)].SetAttributes({
		ItemKey::IronChestplate, ItemTypes::Armor, Rarity::Silver, "Iron Chestplate", 2.0f,
		{
			-5.0f, 0.0f, 20.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 80.0f
		}
	});

	myTypes[static_cast<int>(ItemKey::TrainingSword)].SetAttributes({
		ItemKey::TrainingSword, ItemTypes::Weapon, Rarity::Bronze, "Training Sword", 1.0f,
		{
			5.0f, 2.0f, 2.0f,
			0.0f, 0.0f, 0.0f,
			10.0f, 0.0f
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
