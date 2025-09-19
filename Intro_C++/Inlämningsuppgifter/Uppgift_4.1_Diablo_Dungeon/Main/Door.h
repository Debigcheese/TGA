#pragma once
#include "GameEnums.h"
#include "GameStructs.h"

class Door
{
public:
	Door(int aRoomOneId, int aRoomTwoId, Direction aDirection);

	Direction GetDirectionFrom(int aCurrentRoomId) const;
	Direction Opposite(Direction d) const;
	int GetOtherRoomId(const int aCurrentRoom) const;
	void AddDoorLock(DoorLock aDoorLock);

	bool HasLock() const;
	//void TryBreakLock(const Player& aPlayer);

private:
	int myRoomOneId; //Room on one side of door
	int myRoomTwoId; //Room on other side of door
	Direction myDirection;
	DoorLock myDoorLock{};
};

