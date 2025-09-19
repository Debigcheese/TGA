#include "Door.h"
#include "Room.h"
#include "GameEnums.h"
#include "GameConstants.h"
#include "GameStructs.h"

using namespace GameConstants;

Door::Door(int aRoomOneId, int aRoomTwoId, Direction aDirection) :
	myRoomOneId(aRoomOneId), myRoomTwoId(aRoomTwoId), myDirection(aDirection), myDoorLock()
{

}

Direction Door::GetDirectionFrom(int aCurrentRoomId) const
{
	return aCurrentRoomId == myRoomOneId ? myDirection : Opposite(myDirection);
}

Direction Door::Opposite(Direction d) const
{
	switch (d)
	{
	case Direction::West:
	{
		return Direction::East;
	}
	case Direction::East:
	{
		return Direction::West;
	}
	case Direction::North:
	{
		return Direction::South;
	}
	case Direction::South:
	{
		return Direction::North;
	}
	default:
	{
		return Direction::None;
	}
	}
	return Direction::None;
}


int Door::GetOtherRoomId(const int aCurrentRoomId) const
{
	return aCurrentRoomId == myRoomOneId ? myRoomTwoId : myRoomOneId;
}

void Door::AddDoorLock(DoorLock aDoorLock)
{
	myDoorLock = aDoorLock;
}

bool Door::HasLock() const
{
	return myDoorLock.lockCheck != LockCheck::Unlocked;
}

