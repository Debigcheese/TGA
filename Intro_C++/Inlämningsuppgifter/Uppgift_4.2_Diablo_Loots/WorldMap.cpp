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
	for (Room room : myRooms)
	{
		if (room.GetRoomId() == aRoomId)
		{
			return &room;
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
	Door d1 = Door(0, 10, Direction::Direction_North);
	Door d2 = Door(0, 1, Direction::Direction_East);

	Door d3 = Door(1, 11, Direction::Direction_North);
	Door d4 = Door(10, 11, Direction::Direction_East);

	Door d5 = Door(10, 20, Direction::Direction_North);

	Lock doorLock;
	doorLock.agilityReq.attributeValue = 50;
	doorLock.strengthReq.attributeValue = 10;

	d5.AddDoorLock(doorLock);
	d1.AddDoorLock(doorLock);

	// Room 0 connections
	myRooms.at(0).AddDoor(d1);
	myRooms.at(0).AddDoor(d2);

	// Room 1 connections
	myRooms.at(1).AddDoor(d2);
	myRooms.at(1).AddDoor(d3);

	// Room 2 connections
	myRooms.at(2).AddDoor(d1);
	myRooms.at(2).AddDoor(d4);
	myRooms.at(2).AddDoor(d5);

	// Room 3 connections
	myRooms.at(3).AddDoor(d3);
	myRooms.at(3).AddDoor(d4);

	// Room 4 connections
	myRooms.at(4).AddDoor(d5);



}

void WorldMap::GenerateRooms()
{
	std::vector<Enemy> enemiesR0;
	std::vector<Enemy> enemiesR1;
	std::vector<Enemy> enemiesR2;
	std::vector<Enemy> enemiesR3;
	//std::vector<Enemy> enemiesR4;
	std::vector<Enemy> enemiesR5;

	enemiesR0.push_back(GenerateEnemy(EnemyType::EnemyType_Bat));
	enemiesR0.push_back(GenerateEnemy(EnemyType::EnemyType_Bat));
	enemiesR0.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));

	enemiesR1.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));
	//enemiesR1.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));
	enemiesR1.push_back(GenerateEnemy(EnemyType::EnemyType_Undead));

	//enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Beast));
	//enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Undead));
	//enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Undead));

	enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Skeleton));
	enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Beast));
	enemiesR2.push_back(GenerateEnemy(EnemyType::EnemyType_Humanoid));

	enemiesR3.push_back(GenerateEnemy(EnemyType::EnemyType_Beast));
	enemiesR3.push_back(GenerateEnemy(EnemyType::EnemyType_Elemental));
	enemiesR3.push_back(GenerateEnemy(EnemyType::EnemyType_Humanoid));

	//enemiesR4.push_back(GenerateEnemy(EnemyType::EnemyType_Humanoid));
	////enemiesR4.push_back(GenerateEnemy(EnemyType::EnemyType_Elemental));
	//enemiesR4.push_back(GenerateEnemy(EnemyType::EnemyType_Elemental));

	//enemiesR5.push_back(GenerateEnemy(EnemyType::EnemyType_Elemental));
	enemiesR5.push_back(GenerateEnemy(EnemyType::EnemyType_Demon));
	//enemiesR5.push_back(GenerateEnemy(EnemyType::EnemyType_Elemental));

	myRooms.push_back(Room(0, "Withered Halls", enemiesR0));
	myRooms.push_back(Room(1, "Obsidian Spire", enemiesR1));
	myRooms.push_back(Room(10, "Hollow Cavern", enemiesR2));
	myRooms.push_back(Room(11, "Pits of Torment", enemiesR3));
	//myRooms.push_back(Room(20, "Eternal Abyss", enemiesR4));
	myRooms.push_back(Room(20, "Den of the Blighted", enemiesR5));
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