#pragma once
#include "GameEnums.h"
#include "GameStructs.h"

class Player;

class Door
{
public:
	Door(int aRoomOneId, int aRoomTwoId, Direction aDirection);

	Direction GetDirectionFrom(int aCurrentRoomId) const;
	int GetOtherRoomId(const int aCurrentRoom) const;
	void AddDoorLock(const Lock& aLock);

	bool HasLock() const;
	void PrintDoorLock() const;
	void UpdateDoorLock(const Player& aPlayer);
	bool TryLockPick(const Player& aPlayer, const LockType& aType) const;

private:
	int myRoomOneId; //Room on one side of door
	int myRoomTwoId; //Room on other side of door
	Direction myDirection;
	Lock myLock{};
};
