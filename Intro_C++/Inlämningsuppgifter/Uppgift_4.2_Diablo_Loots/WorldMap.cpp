#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "GameStructs.h"
#include "Chest.h"
#include "ItemDB.h"

using namespace Utils;
using namespace EnemyDB;

WorldMap::WorldMap() : myNextEnemyId(ENEMY_ID_FIRST)
{
}

WorldMap::WorldMap(std::vector<Room> myRooms) : myNextEnemyId(ENEMY_ID_FIRST)
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

Room* WorldMap::GetRoomWithId(int aRoomId) const
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
}

Enemy WorldMap::GenerateEnemy(const EnemyType& aEnemyType)
{
	Enemy enemy(aEnemyType);
	GiveEnemyUniqueId(enemy);
	return enemy;
}

void WorldMap::GiveEnemyUniqueId(Enemy& aEnemy)
{
	int newId = myNextEnemyId;
	myNextEnemyId++;
	aEnemy.SetId(newId);
}

void WorldMap::GenerateDoors()
{
	//room 0
	Door d1 = Door(ROOM_0_ID, ROOM_2_ID);
	Door d2 = Door(ROOM_0_ID, ROOM_1_ID);
	Door d3 = Door(ROOM_1_ID, ROOM_3_ID);
	Door d4 = Door(ROOM_2_ID, ROOM_3_ID);
	Door d5 = Door(ROOM_2_ID, ROOM_4_ID);
	Door d6 = Door(ROOM_4_ID, ROOM_WIN_ID);

	Lock l1;
	l1.agilityReq.attributeValue = LOCK_1_AGILITY_REQ;
	l1.strengthReq.attributeValue = LOCK_1_STRENGTH_REQ;

	Lock l2;
	l2.agilityReq.attributeValue = LOCK_1_STRENGTH_REQ;
	l2.strengthReq.attributeValue = LOCK_1_AGILITY_REQ;

	Lock l3;
	l3.agilityReq.attributeValue = 20.0f;
	l3.strengthReq.attributeValue = 20.0f;

	d1.AddDoorLock(l1);
	d5.AddDoorLock(l2);
	d6.AddDoorLock(l3);

	myDoors.push_back(d1);
	myDoors.push_back(d2);
	myDoors.push_back(d3);
	myDoors.push_back(d4);
	myDoors.push_back(d5);
	myDoors.push_back(d6);
}

void WorldMap::GenerateRooms()
{
	std::vector<Enemy> enemiesR0;
	std::vector<Enemy> enemiesR1;
	std::vector<Enemy> enemiesR2;
	std::vector<Enemy> enemiesR3;
	std::vector<Enemy> enemiesR4;
	std::vector<Enemy> enemiesR5;

	enemiesR0.push_back(GenerateEnemy(EnemyType::Bat));
	enemiesR0.push_back(GenerateEnemy(EnemyType::Bat));
	enemiesR0.push_back(GenerateEnemy(EnemyType::Skeleton));

	enemiesR1.push_back(GenerateEnemy(EnemyType::Skeleton));
	enemiesR1.push_back(GenerateEnemy(EnemyType::Undead));

	enemiesR2.push_back(GenerateEnemy(EnemyType::Skeleton));
	enemiesR2.push_back(GenerateEnemy(EnemyType::Beast));
	enemiesR2.push_back(GenerateEnemy(EnemyType::Humanoid));

	enemiesR3.push_back(GenerateEnemy(EnemyType::Beast));
	enemiesR3.push_back(GenerateEnemy(EnemyType::Elemental));
	enemiesR3.push_back(GenerateEnemy(EnemyType::Humanoid));

	enemiesR4.push_back(GenerateEnemy(EnemyType::Demon));

	AddRoom(Room(ROOM_0_ID, "Withered Halls", {0, 0}, enemiesR0));
	AddRoom(Room(ROOM_1_ID, "Obsidian Spire", {1, 0}, enemiesR1));
	AddRoom(Room(ROOM_2_ID, "Hollow Cavern", {0, 1}, enemiesR2));
	AddRoom(Room(ROOM_3_ID, "Pits of Torment", {1, 1}, enemiesR3));
	AddRoom(Room(ROOM_4_ID, "Den of the Blighted", {0, 2}, enemiesR4));
	AddRoom(Room(ROOM_WIN_ID, "Eternal Abyss", {-1, 2}, enemiesR5));
}

void WorldMap::GenerateChests()
{
	CreateChests(ROOM_0_ID, 1, Rarity::Bronze);
	CreateChests(ROOM_1_ID, 3, Rarity::Gold);
	CreateChests(ROOM_2_ID, 2, Rarity::Legendary);
	CreateChests(ROOM_3_ID, 0, Rarity::None);
	CreateChests(ROOM_4_ID, 1, Rarity::Legendary);
}

void WorldMap::CreateChests(int aRoomId, int aAmount, Rarity aRarity)
{
	std::vector<Chest> chests{};

	if (aAmount < 0)
	{
		return;
	}

	const int COUNT = aAmount;

	chests.reserve(COUNT);
	for (int i = 0; i < COUNT; ++i)
	{
		chests.emplace_back(aRoomId, GetItemsUpToRarity(0, 3, aRarity));
	}
	AddChestsToRoomId(aRoomId, chests);
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
	AddItemsToRoomId(ROOM_0_ID, GetItemsUpToRarity(0, 2, Rarity::Bronze));
	AddItemsToRoomId(ROOM_1_ID, GetItemsUpToRarity(0, 3, Rarity::Silver));
	AddItemsToRoomId(ROOM_2_ID, GetItemsUpToRarity(0, 3, Rarity::Gold));
	AddItemsToRoomId(ROOM_3_ID, GetItemsUpToRarity(1, 2, Rarity::Legendary));
	AddItemsToRoomId(ROOM_4_ID, GetItemsUpToRarity(1, 3, Rarity::Legendary));
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

	if (itemIdPool.empty() || aMaxAmount <= 0)
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
