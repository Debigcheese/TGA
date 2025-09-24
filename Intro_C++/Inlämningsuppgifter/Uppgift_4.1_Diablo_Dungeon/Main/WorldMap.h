#pragma once
#include "Room.h"
#include "Door.h"
#include "Enemy.h"

class WorldMap
{
public:
	WorldMap();
	WorldMap(std::vector<Room> aRooms);

	std::vector<Door>& GetDoors();
	std::vector<Room>& GetRooms();
	Room* GetRoomWithId(int aRoomId);
	Room* GetRoomWithId(int aRoomId) const;

	void AddRoom(const Room& aRoomToAdd);

	void GenerateWorld();
	Enemy GenerateEnemy(const EnemyType& aEnemyType);
	void GiveEnemyRandomId(Enemy& aEnemy);
	void GenerateDoors();
	void GenerateRooms();

private:
	int myNextId;
	std::vector<Room> myRooms;
	std::vector<Door> myDoors;
};
