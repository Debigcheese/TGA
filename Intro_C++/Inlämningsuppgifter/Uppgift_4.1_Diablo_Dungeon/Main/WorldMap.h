#pragma once
#include "Room.h"

class WorldMap
{
public:
	WorldMap();
	WorldMap(std::vector<Room> myRooms);

	std::vector<Room>GetRooms();
	std::vector<Door>GetDoors();

	void AddRoom(Room aRoomToAdd);
	void GenerateWorld();
	void GenerateRandomEnemies();

private:
	std::vector<Room> myRooms;
	std::vector<Door> myDoors;

};

