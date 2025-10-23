#include "Door.h"
#include "Room.h"
#include "GameConstants.h"
#include "Utils.h"
#include "Player.h"

#include "iostream"

using namespace GameConstants;
using namespace Utils;

Door::Door(int aRoomOneId, int aRoomTwoId, const Lock& aLock) :
    myRoomOneId(aRoomOneId),
    myRoomTwoId(aRoomTwoId),
    myLock(aLock)
{
}


bool Door::HasMatchingRoomIds(int aRoomIdOne, int aRoomIdTwo) const
{
    if ((aRoomIdOne == myRoomOneId || aRoomIdOne == myRoomTwoId)
        && (aRoomIdTwo == myRoomOneId || aRoomIdTwo == myRoomTwoId))
    {
        return true;
    }
    return false;
}

bool Door::HasLock() const
{
    return myLock.isLocked;
}

bool Door::TryLockPick(const Player& aPlayer, const LockType& aType) const
{
    if (aType == LockType::Agility)
    {
        if (aPlayer.GetAttributes().agility >= myLock.agilityReq.attributeValue)
        {
            return true;
        }
    }
    if (aType == LockType::Strength)
    {
        if (aPlayer.GetAttributes().strength >= myLock.strengthReq.attributeValue)
        {
            return true;
        }
    }
    return false;
}

const Lock& Door::GetLock() const
{
    return myLock;
}

void Door::SetLock(const Lock& aLock)
{
    myLock = aLock;
}
