#pragma once
#include "GameEnums.h"
#include "GameStructs.h"

class Player;

class Door
{
public:
	Door(int aRoomOneId, int aRoomTwoId, Direction aDirection);

	Direction GetDirectionFrom(int aCurrentRoomId) const;
	Direction Opposite(Direction d) const;
	int GetOtherRoomId(const int aCurrentRoom) const;
	void AddDoorLock(Lock aLock);

	bool HasLock() const;
	const char* LockTypeToString(const LockType& aLockType) const;
	void PrintDoorLock() const;
	void UpdateDoorLock(const Player& aPlayer);
	bool TryLockPick(const Player& aPlayer, const LockType& aType) const;

private:
	int myRoomOneId; //Room on one side of door
	int myRoomTwoId; //Room on other side of door
	Direction myDirection;
	Lock myLock{};
};

