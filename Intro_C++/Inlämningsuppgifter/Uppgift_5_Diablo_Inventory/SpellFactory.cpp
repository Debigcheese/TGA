#include "SpellFactory.h"
#include "Utils.h"

SpellFactory::SpellFactory() : myTypes({})
{
    InitFactory();
}

void SpellFactory::InitFactory()
{
    myTypes.resize(static_cast<int>(SpellKey::Count));

    myTypes[static_cast<int>(SpellKey::MagicMissile)].SetAttributes(
        {
            SpellKey::MagicMissile, Rarity::Bronze, "Magic Missile",
            {
                0.0f, 5.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                25.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::Fireball)].SetAttributes(
        {
            SpellKey::Fireball, Rarity::Silver, "Fireball",
            {
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                75.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::MeteorStrike)].SetAttributes(
        {
            SpellKey::MeteorStrike, Rarity::Gold, "Meteor Strike",
            {
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                125.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::ChainLightning)].SetAttributes(
        {
            SpellKey::ChainLightning, Rarity::Legendary, "Chain Lightning",
            {
                0.0f, 5.0f, 0.0f,
                10.0f, 0.0f, 0.0f,
                175.0f, 0.0f
            }
        }
    );


    myTypes[static_cast<int>(SpellKey::AcidSpray)].SetAttributes(
        {
            SpellKey::AcidSpray, Rarity::Silver, "Acid Spray",
            {
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                45.0f, -15.0f
            }
        }
    );


    myTypes[static_cast<int>(SpellKey::Earthquake)].SetAttributes(
        {
            SpellKey::Earthquake, Rarity::Gold, "Earthquake",
            {
                5.0f, 0.0f, 20.0f,
                0.0f, 0.0f, 0.0f,
                99.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::StoneSkin)].SetAttributes(
        {
            SpellKey::StoneSkin, Rarity::Silver, "Stone Skin",
            {
                0.0f, 0.0f, 30.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 60.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::Shockwave)].SetAttributes(
        {
            SpellKey::Shockwave, Rarity::Bronze, "Shockwave",
            {
                5.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                35.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::PhoenixFlame)].SetAttributes(
        {
            SpellKey::PhoenixFlame, Rarity::Gold, "Phoenix Flame",
            {
                0.0f, 0.0f, 0.0f,
                30.0f, 0.0f, 0.0f,
                120.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::WindSlash)].SetAttributes(
        {
            SpellKey::WindSlash, Rarity::Silver, "Wind Slash",
            {
                0.0f, 15.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                55.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::Hurricane)].SetAttributes(
        {
            SpellKey::Hurricane, Rarity::Legendary, "Hurricane",
            {
                0.0f, 40.0f, 20.0f,
                30.0f, 0.0f, 0.0f,
                180.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::HealingLight)].SetAttributes(
        {
            SpellKey::HealingLight, Rarity::Bronze, "Healing Light",
            {
                0.0f, 0.0f, 0.0f,
                40.0f, 0.0f, 0.0f,
                0.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::DivineShield)].SetAttributes(
        {
            SpellKey::DivineShield, Rarity::Silver, "Divine Shield",
            {
                0.0f, 0.0f, 15.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 80.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::ArcaneBlast)].SetAttributes(
        {
            SpellKey::ArcaneBlast, Rarity::Gold, "Arcane Blast",
            {
                0.0f, 15.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                130.0f, 0.0f
            }
        }
    );

    myTypes[static_cast<int>(SpellKey::BlackHole)].SetAttributes(
        {
            SpellKey::BlackHole, Rarity::Legendary, "Black Hole",
            {
                0.0f, 0.0f, -20.0f,
                0.0f, 0.0f, 0.0f,
                250.0f, 0.0f
            }
        }
    );
}

SpellFactory& SpellFactory::GetFactory()
{
    static SpellFactory instance;
    return instance;
}

Spell SpellFactory::Create(SpellKey aKey)
{
    if (aKey <= SpellKey::None || aKey >= SpellKey::Count || static_cast<int>(aKey) >= static_cast<int>(myTypes.size()))
    {
        aKey = static_cast<SpellKey>(Utils::GenerateRandomNumber
            (static_cast<int>(SpellKey::None) + 1,
             static_cast<int>(myTypes.size()) - 1));
    }
    SpellType& type = myTypes[static_cast<int>(aKey)];
    return {(&type), myNextId++};
}

std::vector<SpellKey> SpellFactory::GetSpellKeysFromRarities(const std::vector<Rarity>& aRarities) const
{
    std::vector<SpellKey> keysWithRarity;
    for (const auto& a : myTypes)
    {
        for (const auto& r : aRarities)
        {
            if (a.GetSpellAttributes().rarity == r)
            {
                keysWithRarity.push_back(a.GetSpellAttributes().key);
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
        spellsInRoom.emplace_back(GetFactory().Create(chosenKey));

        spellIdPool[randomIndex] = spellIdPool.back();
        spellIdPool.pop_back();
    }
    return spellsInRoom;
}
