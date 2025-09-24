#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "GameStructs.h"

using namespace Utils;
using namespace EnemyDB;

WorldMap::WorldMap() : myNextId(ENEMY_ID_FIRST)
{
}

WorldMap::WorldMap(std::vector<Room> myRooms) : myNextId(ENEMY_ID_FIRST)
{
}

std::vector<Room> WorldMap::GetRooms()
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

void WorldMap::AddRoom(Room aRoomToAdd)
{
	myRooms.push_back(aRoomToAdd);
}

void WorldMap::GenerateWorld()
{
	GenerateRooms();
	GenerateDoors();
}

Enemy WorldMap::GenerateEnemy(const EnemyType& aEnemyType)
{
	Enemy enemy(aEnemyType);
	GiveEnemyRandomId(enemy);
	return enemy;
}

void WorldMap::GiveEnemyRandomId(Enemy& aEnemy)
{
	int newId = myNextId;
	myNextId++;
	aEnemy.SetId(newId);
}

void WorldMap::GenerateDoors()
{
	//room 0
	Door d1 = Door(ROOM_0_ID, ROOM_2_ID, Direction::Direction_North);
	Door d2 = Door(ROOM_0_ID, ROOM_1_ID, Direction::Direction_East);

	Door d3 = Door(ROOM_1_ID, ROOM_3_ID, Direction::Direction_North);
	Door d4 = Door(ROOM_2_ID, ROOM_3_ID, Direction::Direction_East);

	Door d5 = Door(ROOM_2_ID, ROOM_4_ID, Direction::Direction_North);

	Door d6 = Door(ROOM_4_ID, ROOM_WIN_ID, Direction::Direction_West);

	Lock doorLock;
	doorLock.agilityReq.attributeValue = LOCK_1_AGILITY_REQ;
	doorLock.strengthReq.attributeValue = LOCK_1_STRENGTH_REQ;

	d5.AddDoorLock(doorLock);
	d1.AddDoorLock(doorLock);

	// Room 0 connections
	myRooms.at(ROOM_0_INDEX).AddDoor(d1);
	myRooms.at(ROOM_0_INDEX).AddDoor(d2);

	// Room 1 connections
	myRooms.at(ROOM_1_INDEX).AddDoor(d2);
	myRooms.at(ROOM_1_INDEX).AddDoor(d3);

	// Room 2 connections
	myRooms.at(ROOM_2_INDEX).AddDoor(d1);
	myRooms.at(ROOM_2_INDEX).AddDoor(d4);
	myRooms.at(ROOM_2_INDEX).AddDoor(d5);

	// Room 3 connections
	myRooms.at(ROOM_3_INDEX).AddDoor(d3);
	myRooms.at(ROOM_3_INDEX).AddDoor(d4);

	// Room 4 connections
	myRooms.at(ROOM_4_INDEX).AddDoor(d5);
	myRooms.at(ROOM_4_INDEX).AddDoor(d6);

	// Room 5 connections
	myRooms.at(ROOM_5_INDEX).AddDoor(d6);
}

void WorldMap::GenerateRooms()
{
	std::vector<Enemy> enemiesR0;
	std::vector<Enemy> enemiesR1;
	std::vector<Enemy> enemiesR2;
	std::vector<Enemy> enemiesR3;
	std::vector<Enemy> enemiesR4;
	std::vector<Enemy> enemiesR5;

	enemiesR0.push_back(GenerateEnemy(EnemyType::EnemyType_Bat));
	enemiesR0.push_back(GenerateEnemy(EnemyType::EnemyType_Bat));
	enemiesR0.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));

	enemiesR1.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));
	enemiesR1.push_back(GenerateEnemy(EnemyType::EnemyType_Undead));

	enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));
	enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Beast));
	enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Humanoid));

	enemiesR3.push_back(GenerateEnemy(EnemyType::EnemyType_Beast));
	enemiesR3.push_back(GenerateEnemy(EnemyType::EnemyType_Elemental));
	enemiesR3.push_back(GenerateEnemy(EnemyType::EnemyType_Humanoid));

	enemiesR4.push_back(GenerateEnemy(EnemyType::EnemyType_Demon));

	myRooms.push_back(Room(ROOM_0_ID, "Withered Halls", enemiesR0));
	myRooms.push_back(Room(ROOM_1_ID, "Obsidian Spire", enemiesR1));
	myRooms.push_back(Room(ROOM_2_ID, "Hollow Cavern", enemiesR2));
	myRooms.push_back(Room(ROOM_3_ID, "Pits of Torment", enemiesR3));
	myRooms.push_back(Room(ROOM_4_ID, "Den of the Blighted", enemiesR4));
	myRooms.push_back(Room(ROOM_WIN_ID, "Eternal Abyss", enemiesR5));
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
