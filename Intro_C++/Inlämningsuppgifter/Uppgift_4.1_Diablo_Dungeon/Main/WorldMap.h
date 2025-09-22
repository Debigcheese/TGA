#pragma once
#include "Room.h"

class WorldMap
{
public:
	WorldMap();
	WorldMap(std::vector<Room> aRooms);

	std::vector<Room>GetRooms();
	Room* GetRoomWithId(int aRoomId);
	Room* GetRoomWithId(int aRoomId) const;

	void AddRoom(Room aRoomToAdd);

	void GenerateWorld();
	void GenerateRandomEnemies();
	void GiveEnemyRandomId(Enemy& enemy);
	void GenerateDoors();
	void GenerateRooms();

private:
	int myNextId = 0;
	std::vector<Room> myRooms;


};

