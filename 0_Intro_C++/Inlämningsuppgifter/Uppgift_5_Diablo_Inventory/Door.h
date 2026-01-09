#pragma once
#include "GameEnums.h"
#include "GameStructs.h"

#include <string>

class Room;
class Player;

class Door
{
public:
    Door(int aRoomOneId, int aRoomTwoId, const Lock& aLock);

    bool HasMatchingRoomIds(int aRoomIdOne, int aRoomIdTwo) const;
    bool HasLock() const;
    bool TryLockPick(const Player& aPlayer, const LockType& aType) const;
    const Lock& GetLock() const;
    void SetLock(const Lock& aLock);

private:
    int myRoomOneId;
    int myRoomTwoId;
    Lock myLock{};
};
