#pragma once
#include "GameEnums.h"
#include "GameStructs.h"

class Room;
class Player;

class Door
{
public:
	Door(int aRoomOneId, int aRoomTwoId);

	void AddDoorLock(const Lock& aLock);
	void UpdateDoorLock(const Player& aPlayer);
	void PrintDoorLock() const;

	bool HasMatchingRoomIds(int aRoomIdOne, int aRoomIdTwo) const;
	int GetOtherRoomId(const int aCurrentRoom) const;
	bool HasLock() const;
	bool TryLockPick(const Player& aPlayer, const LockType& aType) const;

private:
	int myRoomOneId; //Room on one side of door
	int myRoomTwoId; //Room on other side of door
	Lock myLock{};
};
