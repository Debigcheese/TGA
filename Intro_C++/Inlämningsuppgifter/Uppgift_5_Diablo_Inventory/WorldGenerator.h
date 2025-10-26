#pragma once
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Chest.h"
#include "Spell.h"

#include "GameEnums.h"
#include "Player.h"

class WorldGenerator
{
public:
    WorldGenerator();

    void GenerateDoors(std::vector<Door>& aDoors);
    void GenerateRooms(std::vector<Room>& aRooms);

    Room GenerateRoom(int aRoomId);

    std::vector<Enemy> GenerateEnemies(const std::vector<EnemyKey>& aEnemyKeys);
    std::vector<Item> GenerateItems(int aRoomId);
    std::vector<Chest> GenerateChests(int aRoomId);
    std::vector<Spell> GenerateSpells(int aRoomId);

    std::vector<Chest> CreateChestsUpToRarity(int aRoomId, int aMinAmount, int aMaxAmount, Rarity aRarity);

private:
    //world map constants
    struct EnemyRoom
    {
        std::vector<EnemyKey> enemyKeys;
    };

    struct CreateObject
    {
        int id;
        AmountRange amount;
        Rarity rarity;
    };

    //constants
    //ROOMS
    static constexpr int ROOM_0_ID = 0;
    static constexpr int ROOM_1_ID = 1;
    static constexpr int ROOM_2_ID = 2;
    static constexpr int ROOM_3_ID = 3;
    static constexpr int ROOM_4_ID = 4;
    static constexpr int ROOM_5_ID = 5;
    static constexpr int ROOM_WIN_ID = 6;

    static constexpr int ROOM_SIZE = 7;

    RoomMeta myRoomMeta[ROOM_SIZE] = {
        {ROOM_0_ID, "Withered Halls", {0, 0}},
        {ROOM_1_ID, "Obsidian Spire", {1, 0}},
        {ROOM_2_ID, "Hollow Cavern", {0, 1}},
        {ROOM_3_ID, "Pits of Torment", {1, 1}},
        {ROOM_4_ID, "Den of the Blighted", {0, 2}},
        {ROOM_5_ID, "Eternal Abyss", {-1, 2}},
        {ROOM_WIN_ID, "The Dungeon Passage", {-1, 3}},
    };

    //LOCK_DEF
    static constexpr Lock LOCK_UNLOCKED = {
        false,
        {LockType::Strength, 0.0f},
        {LockType::Agility, 0.0f}
    };
    static constexpr Lock LOCK_ONE = {
        true,
        {LockType::Strength, 8.0f},
        {LockType::Agility, 10.0f}
    };
    static constexpr Lock LOCK_TWO = {
        true,
        {LockType::Strength, 10.0f},
        {LockType::Agility, 15.0f}
    };
    static constexpr Lock LOCK_THREE = {
        true,
        {LockType::Strength, 30.0f},
        {LockType::Agility, 30.0f}
    };

    //ENEMIES
    static constexpr AmountRange ENEMY_DROP_ITEM = {0, 1};

    static constexpr int ENEMIES_PER_ROOM_MAX = 3;

    //ENEMY PER ROOM
    const std::vector<EnemyRoom> myEnemyFromID = {
        {{EnemyKey::Bat, EnemyKey::Bat, EnemyKey::Skeleton}},
        {{EnemyKey::Skeleton, EnemyKey::Undead, EnemyKey::None}}, // east first
        {{EnemyKey::Skeleton, EnemyKey::Beast, EnemyKey::Bat}}, //north first
        {{EnemyKey::None, EnemyKey::Humanoid, EnemyKey::Beast}},
        {{EnemyKey::Elemental, EnemyKey::Humanoid, EnemyKey::None}},
        {{EnemyKey::None, EnemyKey::Demon, EnemyKey::None}},
        {{EnemyKey::None, EnemyKey::None, EnemyKey::None}}
    };

    //CHESTS
    static constexpr CreateObject CHEST_FROM_ID[ROOM_SIZE] = {
        {ROOM_0_ID, {0, 1}, Rarity::Bronze},
        {ROOM_1_ID, {0, 2}, Rarity::Silver},
        {ROOM_2_ID, {0, 1}, Rarity::Gold},
        {ROOM_3_ID, {0, 1}, Rarity::Legendary},
        {ROOM_4_ID, {0, 1}, Rarity::Legendary},
        {ROOM_4_ID, {0, 1}, Rarity::Legendary},
    };

    static constexpr AmountRange CHEST_DROP_ITEM = {0, 3};

    //ITEMS
    static constexpr CreateObject ITEM_FROM_ID[ROOM_SIZE] = {
        {ROOM_0_ID, {1, 2}, Rarity::Bronze},
        {ROOM_1_ID, {0, 2}, Rarity::Silver},
        {ROOM_2_ID, {0, 2}, Rarity::Gold},
        {ROOM_3_ID, {0, 2}, Rarity::Legendary},
        {ROOM_4_ID, {1, 3}, Rarity::Legendary},
        {ROOM_4_ID, {1, 3}, Rarity::Legendary},
    };

    //SPELLS
    static constexpr CreateObject SPELL_FROM_ID[ROOM_SIZE] = {
        {ROOM_0_ID, {0, 2}, Rarity::Bronze},
        {ROOM_1_ID, {0, 3}, Rarity::Silver},
        {ROOM_2_ID, {2, 3}, Rarity::Gold},
        {ROOM_3_ID, {1, 2}, Rarity::Legendary},
        {ROOM_4_ID, {1, 3}, Rarity::Legendary},
        {ROOM_4_ID, {1, 3}, Rarity::Legendary},
    };
};
