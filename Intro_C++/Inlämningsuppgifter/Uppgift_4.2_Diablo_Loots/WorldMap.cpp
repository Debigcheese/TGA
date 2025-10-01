#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "GameStructs.h"
#include "Chest.h"
#include "ItemDB.h"
#include "SpellDB.h"

using namespace Utils;

WorldMap::WorldMap() : myNextEnemyId(ENEMY_ID_FIRST), myRooms(), myDoors()
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
			return const_cast<Room*>(&room);
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
	myDoors.emplace_back(ROOM_4_ID, ROOM_WIN_ID, LOCK_THREE);
}

Enemy WorldMap::GenerateEnemy(const EnemyType& aEnemyType)
{
	Enemy enemy(aEnemyType);
	GiveEnemyUniqueId(enemy);
	enemy.SetDropItems(GetItemsUpToRarity(ENEMY_DROP_ITEM.min, ENEMY_DROP_ITEM.max, Rarity::Legendary));
	return enemy;
}

std::vector<Enemy> WorldMap::GenerateEnemies(const EnemyRoom& aEnemyRoom)
{
	std::vector<Enemy> enemies;
	if (aEnemyRoom.enemy_one != EnemyType::None)
	{
		enemies.push_back(GenerateEnemy(aEnemyRoom.enemy_one));
	}
	if (aEnemyRoom.enemy_two != EnemyType::None)
	{
		enemies.push_back(GenerateEnemy(aEnemyRoom.enemy_two));
	}
	if (aEnemyRoom.enemy_three != EnemyType::None)
	{
		enemies.push_back(GenerateEnemy(aEnemyRoom.enemy_three));
	}
	return enemies;
}

void WorldMap::GiveEnemyUniqueId(Enemy& aEnemy)
{
	int newId = myNextEnemyId;
	myNextEnemyId++;
	aEnemy.SetId(newId);
}

void WorldMap::GenerateRooms()
{
	myRooms.emplace_back(
		ROOM_0_ID, "Withered Halls", ROOM_POS_FROM_ID[ROOM_0_ID], GenerateEnemies(ENEMY_FROM_ID[ROOM_0_ID]));

	myRooms.emplace_back(
		ROOM_1_ID, "Obsidian Spire", ROOM_POS_FROM_ID[ROOM_1_ID], GenerateEnemies(ENEMY_FROM_ID[ROOM_1_ID]));

	myRooms.emplace_back(
		ROOM_2_ID, "Hollow Cavern", ROOM_POS_FROM_ID[ROOM_2_ID], GenerateEnemies(ENEMY_FROM_ID[ROOM_2_ID]));

	myRooms.emplace_back(
		ROOM_3_ID, "Pits of Torment", ROOM_POS_FROM_ID[ROOM_3_ID], GenerateEnemies(ENEMY_FROM_ID[ROOM_3_ID]));

	myRooms.emplace_back(
		ROOM_4_ID, "Den of the Blighted", ROOM_POS_FROM_ID[ROOM_4_ID], GenerateEnemies(ENEMY_FROM_ID[ROOM_4_ID]));

	myRooms.emplace_back(
		ROOM_WIN_ID, "Eternal Abyss", ROOM_POS_FROM_ID[ROOM_WIN_ID], GenerateEnemies(ENEMY_FROM_ID[ROOM_WIN_ID]));
}

void WorldMap::GenerateChests()
{
	for (int roomId : GetRoomIds())
	{
		const auto& data = CHEST_FROM_ID[roomId];
		AddChestsToRoomId(roomId,
		                  GetChestsUpToRarity(roomId,
		                                      data.amount.min,
		                                      data.amount.max,
		                                      data.rarity));
	}
}

std::vector<Chest> WorldMap::GetChestsUpToRarity(int aRoomId, int aMinAmount, int aMaxAmount, Rarity aRarity)
{
	std::vector<Chest> chests{};

	if (aMinAmount < 0 || aMaxAmount <= 0 || aMaxAmount < aMinAmount)
	{
		return chests;
	}

	const int RANDOM_SIZE = Utils::GenerateRandomNumber(aMinAmount, aMaxAmount); // amount of items to get

	chests.reserve(RANDOM_SIZE);
	for (int i = 0; i < RANDOM_SIZE; ++i)
	{
		chests.emplace_back(aRoomId, aRarity, GetItemsUpToRarity(CHEST_DROP_ITEM.min, CHEST_DROP_ITEM.max, aRarity));
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
		AddItemsToRoomId(roomId,
		                 GetItemsUpToRarity(data.amount.min,
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

std::vector<Item> WorldMap::GetItemsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const
{
	std::vector<int> itemIdPool = ItemDB::GetIdsFromRarities(GetRaritiesFromMax(aRarity));
	// random item pool with rarities up to "aRarity"

	if (itemIdPool.empty() || aMaxAmount <= 0 || aMaxAmount < aMinAmount)
	{
		return {};
	}

	const int RANDOM_SIZE = Utils::GenerateRandomNumber(aMinAmount, aMaxAmount); // amount of items to get

	std::vector<Item> itemsInRoom = {};
	itemsInRoom.reserve(RANDOM_SIZE);

	for (int i = 0; i < RANDOM_SIZE; ++i)
	{
		//generate random index to pick from my itemIdPool
		int randomIndex = Utils::GenerateRandomNumber(0, static_cast<int>(itemIdPool.size() - 1));
		int chosenId = itemIdPool[randomIndex];
		itemsInRoom.emplace_back(chosenId);

		itemIdPool[randomIndex] = itemIdPool.back();
		itemIdPool.pop_back();
	}
	return itemsInRoom;
}

//spells
void WorldMap::GenerateSpells()
{
	for (int roomId : GetRoomIds())
	{
		const auto& data = SPELL_FROM_ID[roomId];
		AddSpellsToRoomId(roomId,
		                  GetSpellsUpToRarity(data.amount.min,
		                                      data.amount.max,
		                                      data.rarity));
	}


	for (const auto& roomIds : GetRoomIds())
	{
		if (roomIds == SPELL_FROM_ID->id)
		{
			int roomId = SPELL_FROM_ID->id;
			AddItemsToRoomId(roomId,
			                 GetItemsUpToRarity(
				                 SPELL_FROM_ID[roomId].amount.min,
				                 SPELL_FROM_ID[roomId].amount.max,
				                 SPELL_FROM_ID[roomId].rarity));
		}
	}
}

void WorldMap::AddSpellsToRoomId(int aRoomId, const std::vector<Spell>& aSpellsToRoom)
{
	for (auto spell : aSpellsToRoom)
	{
		GetRoomWithId(aRoomId)->AddSpellToRoom(spell);
	}
}

std::vector<Spell> WorldMap::GetSpellsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const
{
	std::vector<int> spellIdPool = SpellDB::GetIdsFromRarities(GetRaritiesFromMax(aRarity));
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
		int chosenId = spellIdPool[randomIndex];
		spellsInRoom.emplace_back(chosenId);

		spellIdPool[randomIndex] = spellIdPool.back();
		spellIdPool.pop_back();
	}
	return spellsInRoom;
}

//OLD IMPLEMENTATION
//std::vector<Item> WorldMap::GenerateItemsWithRarity(const std::vector<Rarity>& aItemRarities) const
//{
//	std::vector<int> itemIdPool = ItemDB::GetIdsFromRarities(aItemRarities);
//
//	const int RANDOM_SIZE = Utils::GenerateRandomNumber(0, 2);
//
//	std::vector<Item> itemsInRoom = {};
//
//	for (int i = 0; i < RANDOM_SIZE; ++i)
//	{
//		int randomIndex = Utils::GenerateRandomNumber(0, static_cast<int>(itemIdPool.size() - 1));
//		int chosenId = itemIdPool[randomIndex];
//		itemsInRoom.emplace_back(chosenId);
//	}
//	return itemsInRoom;
//}


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
