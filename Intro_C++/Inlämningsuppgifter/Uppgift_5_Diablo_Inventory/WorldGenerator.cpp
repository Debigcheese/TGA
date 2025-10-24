#include "WorldGenerator.h"

#include "Utils.h"
#include "GameStructs.h"

#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "SpellFactory.h"

using namespace Utils;

WorldGenerator::WorldGenerator()
{
}

// void WorldGenerator::GenerateWorld()
// {
//     //GenerateRooms();
//     //GenerateDoors();
//     // GenerateItems();
//     // GenerateChests();
//     // GenerateSpells();
// }

void WorldGenerator::GenerateDoors(std::vector<Door>& aDoors)
{
    aDoors.reserve(ROOM_SIZE);
    aDoors.emplace_back(ROOM_0_ID, ROOM_2_ID, LOCK_ONE);
    aDoors.emplace_back(ROOM_0_ID, ROOM_1_ID, LOCK_UNLOCKED);
    aDoors.emplace_back(ROOM_1_ID, ROOM_3_ID, LOCK_UNLOCKED);
    aDoors.emplace_back(ROOM_2_ID, ROOM_3_ID, LOCK_UNLOCKED);
    aDoors.emplace_back(ROOM_2_ID, ROOM_4_ID, LOCK_TWO);
    aDoors.emplace_back(ROOM_4_ID, ROOM_5_ID, LOCK_UNLOCKED);
    aDoors.emplace_back(ROOM_5_ID, ROOM_WIN_ID, LOCK_UNLOCKED);
}

void WorldGenerator::GenerateRooms(std::vector<Room>& aRooms)
{
    aRooms.reserve(ROOM_SIZE);
    aRooms.emplace_back(GenerateRoom(ROOM_0_ID));
    aRooms.emplace_back(GenerateRoom(ROOM_1_ID));
    aRooms.emplace_back(GenerateRoom(ROOM_2_ID));
    aRooms.emplace_back(GenerateRoom(ROOM_3_ID));
    aRooms.emplace_back(GenerateRoom(ROOM_4_ID));
    aRooms.emplace_back(GenerateRoom(ROOM_5_ID));
    aRooms.emplace_back(GenerateRoom(ROOM_WIN_ID));
}

Room WorldGenerator::GenerateRoom(int aRoomId)
{
    return {
        {
            aRoomId,
            myRoomNameFromID[aRoomId],
            ROOM_POS_FROM_ID[aRoomId]
        },
        {
            GenerateEnemies({myEnemyFromID[aRoomId].enemyKeys}),
            GenerateItems(aRoomId),
            GenerateChests(aRoomId),
            GenerateSpells(aRoomId)
        }
    };
}

std::vector<Item> WorldGenerator::GenerateItems(int aRoomId)
{
    const auto& data = ITEM_FROM_ID[aRoomId];
    return {
        ItemFactory::GetFactory().CreateItemsUpToRarity(
            data.amount.min,
            data.amount.max,
            data.rarity)
    };
}

std::vector<Chest> WorldGenerator::GenerateChests(int aRoomId)
{
    const auto& data = CHEST_FROM_ID[aRoomId];
    return (
        CreateChestsUpToRarity(aRoomId,
                               data.amount.min,
                               data.amount.max,
                               data.rarity));
}

std::vector<Spell> WorldGenerator::GenerateSpells(int aRoomId)
{
    const auto& data = SPELL_FROM_ID[aRoomId];
    return (
        SpellFactory::GetFactory().CreateSpellsUpToRarity(
            data.amount.min,
            data.amount.max,
            data.rarity));
}

const std::vector<Enemy>& WorldGenerator::GenerateEnemies(const std::vector<EnemyKey> aEnemyKeys) const
{
    std::vector<Enemy> enemies{};

    for (const auto& key : aEnemyKeys)
    {
        if (key == EnemyKey::None)
        {
            continue;
        }

        enemies.push_back(EnemyFactory::GetFactory().Create(key));
        enemies.back().SetDropItems(ItemFactory::GetFactory().CreateItemsUpToRarity(0, 1, Rarity::Legendary));
    }

    return enemies;
}

std::vector<Chest> WorldGenerator::CreateChestsUpToRarity(int aRoomId, int aMinAmount, int aMaxAmount, Rarity aRarity)
{
    std::vector<Chest> chests{};

    if (aMinAmount < 0 || aMaxAmount <= 0 || aMaxAmount < aMinAmount)
    {
        return chests;
    }

    const int RANDOM_SIZE = GenerateRandomNumber(aMinAmount, aMaxAmount); // amount of items to get

    chests.reserve(RANDOM_SIZE);
    for (int i = 0; i < RANDOM_SIZE; ++i)
    {
        chests.emplace_back(aRoomId, aRarity,
                            ItemFactory::GetFactory().CreateItemsUpToRarity(
                                CHEST_DROP_ITEM.min, CHEST_DROP_ITEM.max, aRarity));
    }
    return chests;
}
