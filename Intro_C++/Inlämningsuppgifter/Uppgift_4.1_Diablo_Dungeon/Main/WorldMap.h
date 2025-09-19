#pragma once
#include "Room.h"

class WorldMap
{
public:
	WorldMap();
	WorldMap(std::vector<Room> aRooms);

	std::vector<Room>GetRooms();
	Room* GetRoomWithId(int aRoomId);

	void AddRoom(Room aRoomToAdd);
	void GenerateWorld();
	void GenerateRandomEnemies();
	void GenerateDoors();
	void GenerateRooms();

private:
	std::vector<Room> myRooms;

};

