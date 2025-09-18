#include "Door.h"

Door::Door(int aDoorId, int aRoomOneId, int aRoomTwoId) : myDoorId(aDoorId), myRoomOneId(aRoomOneId), myRoomTwoId(aRoomTwoId)
{

}

int Door::GetDoorId() const
{
	return myDoorId;
}

int* Door::GetRoomIds() const
{
	int roomIds[2] = {};
	roomIds[0] = myRoomOneId;
	roomIds[1] = myRoomTwoId;
	return roomIds;
}

