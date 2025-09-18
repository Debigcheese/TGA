#include "WorldMap.h"
#include "Room.h"
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

std::vector<Door> WorldMap::GetDoors()
{
	return myDoors;
}

void WorldMap::AddRoom(Room aRoomToAdd)
{
	myRooms.push_back(aRoomToAdd);
}

void WorldMap::GenerateWorld()
{
	//GenerateRandomEnemies();
	Door doorOne = Door(0, 0, 0);
	Door doorTwo = Door(0, 0, 1);
	Door doorThree = Door(0, 0, 2);
	Door doorFour = Door(0, 0, 3);

	myDoors.push_back(doorOne);
	myDoors.push_back(doorTwo);
	myDoors.push_back(doorThree);
	myDoors.push_back(doorFour);

	std::vector<int> myDoorIds;
	myDoorIds.push_back(doorOne.GetDoorId());
	myDoorIds.push_back(doorTwo.GetDoorId());
	myDoorIds.push_back(doorThree.GetDoorId());
	myDoorIds.push_back(doorFour.GetDoorId());

	std::vector<Enemy> enemies;// = myRooms.at(0).GetEnemies();
	myRooms.push_back(Room(0, "Withered Halls", myDoorIds, enemies));



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