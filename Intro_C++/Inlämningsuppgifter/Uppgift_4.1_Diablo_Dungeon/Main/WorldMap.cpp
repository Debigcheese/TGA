#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "GameStructs.h"

using namespace Utils;

WorldMap::WorldMap()
{

}
WorldMap::WorldMap(std::vector<Room> myRooms)
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

void WorldMap::AddRoom(Room aRoomToAdd)
{
	myRooms.push_back(aRoomToAdd);
}

void WorldMap::GenerateWorld()
{
	//GenerateRandomEnemies();


	GenerateRooms();
	GenerateDoors();

	//Room(1, "Crypt of the Forgotten", , myRooms.at(0).GetMyEnemies())
	//FirstRoom.SetRoomId(1)
}

void WorldMap::GenerateRandomEnemies()
{
	int enemyAmount = GenerateRandomNumber(0, 3);

	for (int i = 0; i < enemyAmount; i++)
	{
		Enemy enemy = Enemy(20, 5, EnemyType::EnemyType_Bat);
		GiveEnemyRandomId(enemy);
		myRooms.at(0).AddEnemyToRoom(enemy);
	}
}

void WorldMap::GiveEnemyRandomId(Enemy& enemy)
{
	int newId = myNextId;
	myNextId++;
	enemy.SetId(newId);
}

void WorldMap::GenerateDoors()
{
	Door d0 = Door(0, 1, Direction::West);
	Door d1 = Door(0, 2, Direction::North);
	Door d2 = Door(0, 3, Direction::East);

	Door d3 = Door(1, 3, Direction::North);
	Door d4 = Door(1, 4, Direction::East);

	Door d5 = Door(2, 3, Direction::East);
	Door d6 = Door(2, 5, Direction::North);

	Door d7 = Door(3, 4, Direction::West);
	Door d8 = Door(3, 5, Direction::East);

	// Room 0 connections
	myRooms.at(0).AddDoor(d0);
	myRooms.at(0).AddDoor(d1);
	myRooms.at(0).AddDoor(d2);

	// Room 1 connections
	myRooms.at(1).AddDoor(d0);
	myRooms.at(1).AddDoor(d3);
	myRooms.at(1).AddDoor(d4);

	// Room 2 connections
	myRooms.at(2).AddDoor(d1);
	myRooms.at(2).AddDoor(d5);
	myRooms.at(2).AddDoor(d6);

	// Room 3 connections
	myRooms.at(3).AddDoor(d2);
	myRooms.at(3).AddDoor(d3);
	myRooms.at(3).AddDoor(d5);
	myRooms.at(3).AddDoor(d7);
	myRooms.at(3).AddDoor(d8);

	DoorLock agilityLock = { LockCheck::Agility , 50 };
	for (Door& d : myRooms.at(3).GetDoorsConnected())
	{
		d.AddDoorLock(agilityLock);
	}

	// Room 4 connections
	myRooms.at(4).AddDoor(d4);
	myRooms.at(4).AddDoor(d7);

	// Room 5 connections
	myRooms.at(5).AddDoor(d6);
	myRooms.at(5).AddDoor(d8);

}

void WorldMap::GenerateRooms()
{
	std::vector<Enemy> enemies;
	Enemy enemy = Enemy(20, 5, EnemyType::EnemyType_Bat);
	GiveEnemyRandomId(enemy);

	enemies.push_back(enemy);
	enemies.push_back(enemy);

	myRooms.push_back(Room(0, "Withered Halls", enemies));
	myRooms.push_back(Room(1, "Obsidian Spire", enemies));
	myRooms.push_back(Room(2, "Hollow Cavern", enemies));
	myRooms.push_back(Room(3, "Pits of Torment", enemies));
	myRooms.push_back(Room(4, "Eternal Abyss", enemies));
	myRooms.push_back(Room(5, "Den of the Blighted", enemies));
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