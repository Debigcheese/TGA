#include "WorldMap.h"
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"

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

Room WorldMap::GetRoomWithId(const int aRoomId)
{
	for (int i = 0; i < myRooms.size();i++)
	{
		if (myRooms.at(i).GetRoomId() == aRoomId)
		{
			return myRooms.at(i);
		}
	}
	return myRooms.at(0);
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
		Enemy enemy = Enemy(20, 5);
		myRooms.at(0).AddEnemyToRoom(enemy);
	}
}

void WorldMap::GenerateDoors()
{
	Door room0door0 = Door(0, 1);
	Door room0door1 = Door(0, 2);
	Door room0door2 = Door(0, 3);

	Door room1door0 = Door(1, 3);
	Door room1door1 = Door(1, 4);

	Door room2door0 = Door(2, 3);
	Door room2door1 = Door(2, 5);

	Door room3door0 = Door(3, 4);
	Door room3door1 = Door(3, 5);

	myRooms.at(0).AddDoor(room0door0);
	myRooms.at(0).AddDoor(room0door1);
	myRooms.at(0).AddDoor(room0door2);

	myRooms.at(1).AddDoor(room1door0);
	myRooms.at(1).AddDoor(room1door1);

	myRooms.at(2).AddDoor(room2door0);
	myRooms.at(2).AddDoor(room2door1);

	myRooms.at(3).AddDoor(room3door0);
	myRooms.at(3).AddDoor(room3door1);

	myRooms.at(4).AddDoor(room1door1);
	myRooms.at(4).AddDoor(room3door0);

	myRooms.at(5).AddDoor(room2door1);
	myRooms.at(5).AddDoor(room3door1);

}

void WorldMap::GenerateRooms()
{
	std::vector<Enemy> enemies;
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