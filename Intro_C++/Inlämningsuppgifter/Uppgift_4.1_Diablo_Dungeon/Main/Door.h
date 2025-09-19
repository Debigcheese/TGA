#pragma once
#include "Room.h"
#include "GameEnums.h"

class Door
{
public:
	Door(int aRoomOneId, int aRoomTwoId);

	Direction GetDoorPOSFromCurrentRoomId(int aCurrentRoomId);
	int GetOtherRoomId(const int aCurrentRoom) const;
	int GetRoomIdDifference();

private:
	int myRoomOneId; //Room on one side of door
	int myRoomTwoId; //Room on other side of door
};

