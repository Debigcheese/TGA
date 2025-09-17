#pragma once
#include "Room.h"

class Door
{
public:
	Door(int aRoomOneId, int aRoomTwoId);

	void OpenDoor();

private:
	int myRoomOneId;
	int myRoomTwoId;
};

