#pragma once
#include "Room.h"

class WorldMap
{
public:
	WorldMap(std::vector<Room> myRooms);

	std::vector<Room>GetRooms();
	void AddRoom(Room aRoomToAdd);
	void GenerateWorld();
	void GenerateRandomEnemies();

private:
	std::vector<Room> myRooms;

};

