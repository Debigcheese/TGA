#pragma once
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Chest.h"
#include "Spell.h"

#include "GameEnums.h"
#include "Player.h"

class WorldMap
{
public:
	WorldMap();

	//rooms & doors
	std::vector<Door>& GetDoors();
	std::vector<Room>& GetRooms();
	Room* GetRoomWithId(int aRoomId);
	const Room* GetRoomWithId(int aRoomId) const;
	std::vector<int> GetRoomIds() const;
	void AddRoom(const Room& aRoomToAdd);

	void GenerateWorld();
	void GenerateDoors();
	void GenerateRooms();

	static bool HasRoom(int x, int y);
	void PrintMap(Position player);

	Position GetWinRoomPos() const { return GetRoomWithId(ROOM_WIN_ID)->GetPosition(); }
	bool GetReachedWinRoom(const Position& aPosition) const;

	std::vector<Position> GetRoomPositions() const;

	//generate enemies per room
	std::vector<Enemy> GenerateEnemies(std::vector<EnemyKey> aEnemyKeys);

	//items per room
	void GenerateItems();
	void AddItemsToRoomId(int aRoomId, const std::vector<Item>& aItemsToRoom);

	//chests per room
	void GenerateChests();
	std::vector<Chest> CreateChestsUpToRarity(int aRoomId, int aMinAmount, int aMaxAmount, Rarity aRarity);
	void AddChestsToRoomId(int aRoomId, const std::vector<Chest>& aChestsToRoom);

	//spells per room
	void GenerateSpells();
	void AddSpellsToRoomId(int aRoomId, const std::vector<Spell>& aSpellsToRoom);

private:
	std::vector<Room> myRooms;
	std::vector<Door> myDoors;

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

	static constexpr Position ROOM_POS_FROM_ID[ROOM_SIZE] = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1},
		{0, 2},
		{-1, 2},
		{-1, 3}
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
		{LockType::Strength, 25.0f},
		{LockType::Agility, 25.0f}
	};

	//ENEMIES
	static constexpr AmountRange ENEMY_DROP_ITEM = {0, 1};

	//ENEMY PER ROOM
	const std::vector<EnemyRoom> ENEMY_FROM_ID = {
		{{EnemyKey::Bat, EnemyKey::Bat, EnemyKey::Skeleton}},
		{{EnemyKey::Skeleton, EnemyKey::Undead, EnemyKey::None}}, // east first
		{{EnemyKey::Skeleton, EnemyKey::Beast, EnemyKey::Bat}}, //north first
		{{EnemyKey::None, EnemyKey::Humanoid, EnemyKey::Beast}},
		{{EnemyKey::Elemental, EnemyKey::Humanoid, EnemyKey::Beast}},
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
