#include "Door.h"
#include "Room.h"
#include "GameConstants.h"
#include "Utils.h"
#include "Player.h"

#include "iostream"

using namespace GameConstants;
using namespace Utils;

Door::Door(int aRoomOneId, int aRoomTwoId) :
	myRoomOneId(aRoomOneId),
	myRoomTwoId(aRoomTwoId),
	myLock{
		false,
		LockRequirements{LockType::Agility, 0},
		LockRequirements{LockType::Strength, 0},
	}
{
}

int Door::GetOtherRoomId(const int aCurrentRoomId) const
{
	if (aCurrentRoomId == myRoomOneId) return myRoomTwoId;
	if (aCurrentRoomId == myRoomTwoId) return myRoomOneId;
	std::cout << ("fromId not connected to this door");
	system("pause");
	return 0;
}

void Door::AddDoorLock(const Lock& aLock)
{
	myLock = aLock;
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

void Door::PrintDoorLock() const
{
	std::cout << "\n<--- Door is Locked --->\n";
	std::cout << "Required " << LockTypeToString(myLock.agilityReq.lockType) << ": "
		<< myLock.agilityReq.attributeValue << " to lock-pick the door\n";

	std::cout << "Required " << LockTypeToString(myLock.strengthReq.lockType) << ": "
		<< myLock.strengthReq.attributeValue << " to break open the door\n";
}

void Door::UpdateDoorLock(const Player& aPlayer)
{
	PrintDoorLock();
	while (true && !aPlayer.IsDead())
	{
		std::cout
			<< "1) Try Lock-Pick\n"
			<< "2) Try Breaking\n"
			<< "3) Return\n"
			<< "Choice: ";
		int lockChoice = Utils::ReadIntInRange(static_cast<int>(LockType::Agility),
		                                       static_cast<int>(LockType::Unlocked));
		LockType tempLockType = static_cast<LockType>(lockChoice);

		switch (tempLockType)
		{
		case LockType::Agility:
			{
				if (TryLockPick(aPlayer, LockType::Agility))
				{
					std::cout << "\nYou successfully lock-picked the door open!\n";
					myLock.isLocked = false;
					return;
				}
				else
				{
					std::cout << "Your agility is too low: " << aPlayer.GetAttributes().agility << "/" << myLock.
						agilityReq.attributeValue << "\n";
				}
				break;
			}
		case LockType::Strength:
			{
				if (TryLockPick(aPlayer, LockType::Strength))
				{
					std::cout << "\nYou successfully broke the door open!\n";
					myLock.isLocked = false;
					return;
				}
				else
				{
					std::cout << "Your Strength is too low: " << aPlayer.GetAttributes().strength << "/" << myLock.
						strengthReq.attributeValue << "\n";
				}
				break;
			}
		case LockType::Unlocked:
			{
				return;
			}
		case LockType::None:
			{
				return;
			}
		}
		system("pause");
	}
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
