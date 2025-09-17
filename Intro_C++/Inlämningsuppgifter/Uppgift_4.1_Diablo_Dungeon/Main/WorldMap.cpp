#include "WorldMap.h"
#include "Room.h"
#include "Enemy.h"
#include "Utils.h"

using namespace Utils;

WorldMap::WorldMap(std::vector<Room> myRooms)
{

}

std::vector<Room> WorldMap::GetRooms()
{
	return myRooms;
}

void WorldMap::AddRoom(Room aRoomToAdd)
{
	myRooms.push_back(aRoomToAdd);
}

void WorldMap::GenerateWorld()
{
	Door(1, 2);
	Door(1, 3);
	myRooms.at(0);
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