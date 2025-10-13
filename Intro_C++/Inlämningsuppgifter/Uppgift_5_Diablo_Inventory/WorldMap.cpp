#include "WorldMap.h"
#include "Utils.h"
#include "GameStructs.h"

#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "SpellFactory.h"

#include <iostream>

using namespace Utils;

WorldMap::WorldMap() :
	myRooms(),
	myDoors()

{
}

std::vector<Door>& WorldMap::GetDoors()
{
	return myDoors;
}

std::vector<Room>& WorldMap::GetRooms()
{
	return myRooms;
}

Room* WorldMap::GetRoomWithId(const int aRoomId)
{
	for (Room& room : myRooms)
	{
		if (room.GetRoomId() == aRoomId)
		{
			return &room;
		}
	}
	return nullptr;
}

const Room* WorldMap::GetRoomWithId(int aRoomId) const
{
	for (const Room& room : myRooms)
	{
		if (room.GetRoomId() == aRoomId)
		{
			return &room;
		}
	}
	return nullptr;
}

std::vector<int> WorldMap::GetRoomIds() const
{
	std::vector<int> roomIds;
	for (const auto& room : myRooms)
	{
		roomIds.push_back(room.GetRoomId());
	}
	return roomIds;
}

void WorldMap::AddRoom(const Room& aRoomToAdd)
{
	myRooms.push_back(aRoomToAdd);
}

void WorldMap::GenerateWorld()
{
	GenerateRooms();
	GenerateDoors();
	GenerateItems();
	GenerateChests();
	GenerateSpells();
}

void WorldMap::GenerateDoors()
{
	myDoors.emplace_back(ROOM_0_ID, ROOM_2_ID, LOCK_ONE);
	myDoors.emplace_back(ROOM_0_ID, ROOM_1_ID, LOCK_UNLOCKED);
	myDoors.emplace_back(ROOM_1_ID, ROOM_3_ID, LOCK_UNLOCKED);
	myDoors.emplace_back(ROOM_2_ID, ROOM_3_ID, LOCK_UNLOCKED);
	myDoors.emplace_back(ROOM_2_ID, ROOM_4_ID, LOCK_TWO);
	myDoors.emplace_back(ROOM_4_ID, ROOM_5_ID, LOCK_UNLOCKED);
	myDoors.emplace_back(ROOM_5_ID, ROOM_WIN_ID, LOCK_UNLOCKED);
}

void WorldMap::GenerateRooms()
{
	myRooms.emplace_back(
		ROOM_0_ID, "Withered Halls", ROOM_POS_FROM_ID[ROOM_0_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_0_ID].enemyKeys}));

	myRooms.emplace_back(
		ROOM_1_ID, "Obsidian Spire", ROOM_POS_FROM_ID[ROOM_1_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_1_ID].enemyKeys}));

	myRooms.emplace_back(
		ROOM_2_ID, "Hollow Cavern", ROOM_POS_FROM_ID[ROOM_2_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_2_ID].enemyKeys}));

	myRooms.emplace_back(
		ROOM_3_ID, "Pits of Torment", ROOM_POS_FROM_ID[ROOM_3_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_3_ID].enemyKeys}));

	myRooms.emplace_back(
		ROOM_4_ID, "Den of the Blighted", ROOM_POS_FROM_ID[ROOM_4_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_4_ID].enemyKeys}));

	myRooms.emplace_back(
		ROOM_5_ID, "Eternal Abyss", ROOM_POS_FROM_ID[ROOM_5_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_5_ID].enemyKeys}));

	myRooms.emplace_back(
		ROOM_WIN_ID, "The Dungeon Passage", ROOM_POS_FROM_ID[ROOM_WIN_ID],
		GenerateEnemies({ENEMY_FROM_ID[ROOM_WIN_ID].enemyKeys}));
}

bool WorldMap::HasRoom(int x, int y)
{
	for (const auto& p : ROOM_POS_FROM_ID)
	{
		if (p.X == x && p.Y == y)
		{
			return true;
		}
	}
	return false;
}

void WorldMap::PrintMap(const Position player)
{
	constexpr int minX = -2;
	constexpr int maxX = 2;
	constexpr int minY = -1;
	constexpr int maxY = 3;
	
	std::cout << '\n';
	for (int y = maxY; y >= minY; --y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			if (!HasRoom(x, y))
			{
				std::cout << "   ";
				continue;
			}
			if (ROOM_POS_FROM_ID[ROOM_WIN_ID] == Position{x, y})
			{
				std::cout << "[X]";
			}
			else
			{
				std::cout << ((player.X == x && player.Y == y) ? "[O]" : "[ ]");
			}
		}
		std::cout << '\n';
	}
}

bool WorldMap::GetReachedWinRoom(const Position& aPosition) const
{
	return aPosition == GetRoomWithId(ROOM_WIN_ID)->GetPosition();
}

std::vector<Position> WorldMap::GetRoomPositions() const
{
	std::vector<Position> positions;
	positions.reserve(ROOM_SIZE);
	for (const auto& room : myRooms)
	{
		positions.push_back(room.GetPosition());
	}
	return positions;
}

std::vector<Enemy> WorldMap::GenerateEnemies(const std::vector<EnemyKey> aEnemyKeys)
{
	std::vector<Enemy> enemies;

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

void WorldMap::GenerateChests()
{
	for (int roomId : GetRoomIds())
	{
		const auto& data = CHEST_FROM_ID[roomId];
		AddChestsToRoomId(roomId,
		                  CreateChestsUpToRarity(roomId,
		                                         data.amount.min,
		                                         data.amount.max,
		                                         data.rarity));
	}
}

std::vector<Chest> WorldMap::CreateChestsUpToRarity(int aRoomId, int aMinAmount, int aMaxAmount, Rarity aRarity)
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

void WorldMap::AddChestsToRoomId(int aRoomId, const std::vector<Chest>& aChestsToRoom)
{
	for (const auto& chest : aChestsToRoom)
	{
		GetRoomWithId(aRoomId)->AddChestToRoom(chest);
	}
}

void WorldMap::GenerateItems()
{
	for (int roomId : GetRoomIds())
	{
		const auto& data = ITEM_FROM_ID[roomId];
		AddItemsToRoomId(roomId, ItemFactory::GetFactory().CreateItemsUpToRarity(
			                 data.amount.min,
			                 data.amount.max,
			                 data.rarity));
	}
}

void WorldMap::AddItemsToRoomId(int aRoomId, const std::vector<Item>& aItemsToRoom)
{
	for (auto item : aItemsToRoom)
	{
		GetRoomWithId(aRoomId)->AddItemToRoom(item);
	}
}

//spells
void WorldMap::GenerateSpells()
{
	for (int roomId : GetRoomIds())
	{
		const auto& data = SPELL_FROM_ID[roomId];
		AddSpellsToRoomId(roomId,
		                  SpellFactory::GetFactory().CreateSpellsUpToRarity(
			                  data.amount.min,
			                  data.amount.max,
			                  data.rarity));
	}
}

void WorldMap::AddSpellsToRoomId(int aRoomId, const std::vector<Spell>& aSpellsToRoom)
{
	for (auto spell : aSpellsToRoom)
	{
		GetRoomWithId(aRoomId)->AddSpellToRoom(spell);
	}
}

//Crypt of the Forgotten
//The Hollow Catacombs
//Bloodfang Caverns
//Sanctum of Ashes
//The Withered Halls
//Pits of Torment
//Obsidian Spire
//Den of the Blighted
//The Shattered Sepulcher
//Abyss of Eternal Hunger
