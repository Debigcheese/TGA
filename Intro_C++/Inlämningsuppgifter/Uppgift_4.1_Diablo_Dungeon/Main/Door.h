#pragma once
#include "Room.h"

class Door
{
public:
	Door(int aDoorId, int aRoomOneId, int aRoomTwoId);

	int GetDoorId() const;
	int* GetRoomIds() const;

private:
	int myDoorId; //which room this door is in
	int myRoomOneId; //Room on one side of door
	int myRoomTwoId; //Room on other side of door
};

