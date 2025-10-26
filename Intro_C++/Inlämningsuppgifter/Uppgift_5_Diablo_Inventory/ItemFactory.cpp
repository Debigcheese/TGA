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
    return {(&type), myNextId++}; // returns Item address with pointer to type
}

void ItemFactory::InitFactory()
{
    myTypes.resize(static_cast<int>(ItemKey::Count));

    myTypes[static_cast<int>(ItemKey::Eclipse)].SetItemAttributes({
        ItemKey::Eclipse, EquipmentType::Hand, Rarity::Bronze, "Eclipse", 1.0f,
        {
            8.0f, 5.0f, 5.0f,
            0.0f, 0.0f, 0.0f,
            40.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::GodSword)].SetItemAttributes({
        ItemKey::GodSword, EquipmentType::Hand, Rarity::Legendary, "GodSword", 3.0f,
        {
            16.0f, 9.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            80.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::Aegis)].SetItemAttributes({
        ItemKey::Aegis, EquipmentType::Body, Rarity::Bronze, "Aegis", 1.0f,
        {
            0.0f, -4.0f, 18.0f,
            0.0f, 0.0f, 2.0f,
            0.0f, 50.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::Backpack)].SetItemAttributes({
        ItemKey::Backpack, EquipmentType::Amulet, Rarity::Gold, "Backpack", 0.0f,
        {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f,
            0.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::StormBreaker)].SetItemAttributes({
        ItemKey::StormBreaker, EquipmentType::Hand, Rarity::Silver, "Storm Breaker", 2.0f,
        {
            12.0f, 5.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            45.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::DragonScale)].SetItemAttributes({
        ItemKey::DragonScale, EquipmentType::Body, Rarity::Gold, "Dragon Scale", 3.0f,
        {
            5.0f, 0.0f, 45.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 100.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::KnightHelm)].SetItemAttributes({
        ItemKey::KnightHelm, EquipmentType::Head, Rarity::Silver, "Knight Helm", 1.0f,
        {
            0.0f, 0.0f, 18.0f,
            0.0f, 0.0f, 2.0f,
            0.0f, 24.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::BloodFang)].SetItemAttributes({
        ItemKey::BloodFang, EquipmentType::Hand, Rarity::Gold, "Blood Fang", 2.0f,
        {
            8.0f, 8.0f, -2.0f,
            0.0f, 0.0f, 0.0f,
            50.0f, -8.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::CelestialShield)].SetItemAttributes({
        ItemKey::CelestialShield, EquipmentType::Body, Rarity::Legendary, "Celestial Shield", 2.0f,
        {
            0.0f, 0.0f, 25.0f,
            0.0f, 0.0f, 4.0f,
            0.0f, 95.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::WarAxe)].SetItemAttributes({
        ItemKey::WarAxe, EquipmentType::Hand, Rarity::Silver, "War Axe", 2.0f,
        {
            15.0f, -2.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            46.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::LeatherBoots)].SetItemAttributes({
        ItemKey::LeatherBoots, EquipmentType::Feet, Rarity::Bronze, "Leather Boots", 1.0f,
        {
            0.0f, 3.0f, 4.0f,
            0.0f, 0.0f, 2.0f,
            0.0f, 10.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::VoidReaver)].SetItemAttributes({
        ItemKey::VoidReaver, EquipmentType::Hand, Rarity::Legendary, "Void Reaver", 3.0f,
        {
            15.0f, 15.0f, -8.0f,
            0.0f, 0.0f, 0.0f,
            130.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::IronChestplate)].SetItemAttributes({
        ItemKey::IronChestplate, EquipmentType::Body, Rarity::Silver, "Iron Chestplate", 2.0f,
        {
            -4.0f, 0.0f, 20.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 78.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::TrainingSword)].SetItemAttributes({
        ItemKey::TrainingSword, EquipmentType::Hand, Rarity::Bronze, "Training Sword", 1.0f,
        {
            5.0f, 2.0f, 2.0f,
            0.0f, 0.0f, 0.0f,
            10.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::SwiftGreaves)].SetItemAttributes({
        ItemKey::SwiftGreaves, EquipmentType::Feet, Rarity::Silver, "Swift Greaves", 1.0f,
        {
            0.0f, 6.0f, 6.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 16.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::TitanGauntlets)].SetItemAttributes({
        ItemKey::TitanGauntlets, EquipmentType::Hand, Rarity::Gold, "Titan Gauntlets", 1.0f,
        {
            6.0f, -2.0f, 10.0f,
            0.0f, 0.0f, 1.0f,
            12.0f, 28.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::CrusaderPlate)].SetItemAttributes({
        ItemKey::CrusaderPlate, EquipmentType::Body, Rarity::Gold, "Crusader Plate", 3.0f,
        {
            4.0f, -2.0f, 30.0f,
            0.0f, 0.0f, 0.0f,
            6.0f, 110.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::ShadowstepBoots)].SetItemAttributes({
        ItemKey::ShadowstepBoots, EquipmentType::Feet, Rarity::Silver, "Shadowstep Boots", 1.0f,
        {
            0.0f, 8.0f, 2.0f,
            0.0f, 0.0f, 2.0f,
            8.0f, 6.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::BerserkerAmulet)].SetItemAttributes({
        ItemKey::BerserkerAmulet, EquipmentType::Amulet, Rarity::Gold, "Berserker Amulet", 0.0f,
        {
            10.0f, 0.0f, -6.0f,
            0.0f, 0.0f, 0.0f,
            22.0f, -10.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::QuartzAmulet)].SetItemAttributes({
        ItemKey::QuartzAmulet, EquipmentType::Amulet, Rarity::Bronze, "Quartz Amulet", 0.0f,
        {
            0.0f, 2.0f, 2.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 6.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::Sunpiercer)].SetItemAttributes({
        ItemKey::Sunpiercer, EquipmentType::Hand, Rarity::Gold, "Sunpiercer", 2.0f,
        {
            7.0f, 11.0f, -2.0f,
            0.0f, 0.0f, 0.0f,
            55.0f, 4.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::ThunderMaul)].SetItemAttributes({
        ItemKey::ThunderMaul, EquipmentType::Hand, Rarity::Legendary, "Thunder Maul", 3.0f,
        {
            20.0f, -6.0f, 6.0f,
            0.0f, 0.0f, 0.0f,
            100.0f, 10.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::OakheartChest)].SetItemAttributes({
        ItemKey::OakheartChest, EquipmentType::Body, Rarity::Bronze, "Oakheart Chest", 2.0f,
        {
            2.0f, -2.0f, 16.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 22.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::SteelKneeguards)].SetItemAttributes({
        ItemKey::SteelKneeguards, EquipmentType::Legs, Rarity::Silver, "Steel Kneeguards", 1.0f,
        {
            -1.0f, 0.0f, 14.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 20.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::FalconAmulet)].SetItemAttributes({
        ItemKey::FalconAmulet, EquipmentType::Amulet, Rarity::Silver, "Falcon Amulet", 0.0f,
        {
            2.0f, 6.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            10.0f, 0.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::VanguardHelm)].SetItemAttributes({
        ItemKey::VanguardHelm, EquipmentType::Head, Rarity::Legendary, "Vanguard Helm", 2.0f,
        {
            4.0f, 4.0f, 18.0f,
            0.0f, 0.0f, 0.0f,
            12.0f, 40.0f
        }
    });

    myTypes[static_cast<int>(ItemKey::ForgemasterGloves)].SetItemAttributes({
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
        itemsInRoom.emplace_back(GetFactory().Create(chosenKey));

        itemKeyPool[randomIndex] = itemKeyPool.back();
        itemKeyPool.pop_back();
    }
    return itemsInRoom;
}
