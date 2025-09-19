#include "Door.h"
#include "Room.h"
#include "GameEnums.h"
#include "GameConstants.h"

using namespace GameConstants;

Door::Door(int aRoomOneId, int aRoomTwoId) : myRoomOneId(aRoomOneId), myRoomTwoId(aRoomTwoId)
{

}


Direction Door::GetDoorPOSFromCurrentRoomId(int aCurrentRoomId)
{
	Direction doorPos = Direction::None;

	int difference = aCurrentRoomId - GetOtherRoomId(aCurrentRoomId);
	if (difference < 0)
	{
		difference = -difference;
	}

	switch (difference)
	{
	case 1:
	{
		doorPos = Direction::Left;
		break;
	}
	case 2:
	{
		doorPos = Direction::Front;
		break;
	}
	case 3:
	{
		doorPos = Direction::Right;
		break;
	}
	case 4:
	{
		doorPos = Direction::Back;
		break;
	}
	default:
	{
		doorPos = Direction::None;
		break;
	}
	}
	return doorPos;
}


int Door::GetOtherRoomId(const int aCurrentRoomId) const
{
	if (aCurrentRoomId == myRoomOneId)
	{
		return myRoomTwoId;
	}
	return myRoomOneId;
}

int Door::GetRoomIdDifference()
{
	int difference = myRoomOneId - myRoomTwoId;
	if (difference < 0)
	{
		difference = -difference;
	}
	return difference;
}

bool Door::HasRoomId(int aRoomId)
{
	if (myRoomOneId == aRoomId || myRoomTwoId == aRoomId)
	{
		return true;
	}
	return false;
}

