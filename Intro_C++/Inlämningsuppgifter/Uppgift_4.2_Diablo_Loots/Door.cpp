#include "Door.h"
#include "Room.h"
#include "GameConstants.h"
#include "Utils.h"
#include "Player.h"

#include "iostream"

using namespace GameConstants;

Door::Door(int aRoomOneId, int aRoomTwoId, Direction aDirection) :
	myRoomOneId(aRoomOneId), myRoomTwoId(aRoomTwoId), myDirection(aDirection)
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
	case Direction::Direction_West:
	{
		return Direction::Direction_East;
	}
	case Direction::Direction_East:
	{
		return Direction::Direction_West;
	}
	case Direction::Direction_North:
	{
		return Direction::Direction_South;
	}
	case Direction::Direction_South:
	{
		return Direction::Direction_North;
	}
	default:
	{
		return Direction::Direction_None;
	}
	}
	return Direction::Direction_None;
}


int Door::GetOtherRoomId(const int aCurrentRoomId) const
{
	if (aCurrentRoomId == myRoomOneId) return myRoomTwoId;
	if (aCurrentRoomId == myRoomTwoId) return myRoomOneId;
	std::cout << ("fromId not connected to this door");
	system("pause");
}

void Door::AddDoorLock(Lock aLock)
{
	myLock = aLock;
}

bool Door::HasLock() const
{
	return myLock.isLocked;
}

const char* Door::LockTypeToString(const LockType& aLockType) const
{
	switch (aLockType)
	{
	case LockType::LockType_Unlocked:
	{
		return "Unlocked";
	}
	case LockType::LockType_Agility:
	{
		return "Agility";
	}
	case LockType::LockType_Strength:
	{
		return "Strength";
	}
	}
	return nullptr;
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
		int lockChoice = Utils::ReadIntInRange(static_cast<int>(LockType::LockType_Agility), static_cast<int>(LockType::LockType_Unlocked));
		LockType tempLockType = static_cast<LockType>(lockChoice);

		switch (tempLockType)
		{
		case LockType::LockType_Agility:
		{
			if (TryLockPick(aPlayer, LockType::LockType_Agility))
			{
				std::cout << "\nYou successfully lock-picked the door open!\n";
				myLock.isLocked = false;
				return;
			}
			else
			{
				std::cout << "Your agility is too low: " << aPlayer.GetAttributes().agility << "/" << myLock.agilityReq.attributeValue << "\n";
			}
			break;
		}
		case LockType::LockType_Strength:
		{
			if (TryLockPick(aPlayer, LockType::LockType_Strength))
			{
				std::cout << "\nYou successfully broke the door open!\n";
				myLock.isLocked = false;
				return;
			}
			else
			{
				std::cout << "Your Strength is too low: " << aPlayer.GetAttributes().strength << "/" << myLock.strengthReq.attributeValue << "\n";
			}
			break;
		}
		case LockType::LockType_Unlocked:
		{
			return;
		}
		}
		system("pause");
	}
}

bool Door::TryLockPick(const Player& aPlayer, const LockType& aType) const
{
	if (aType == LockType::LockType_Agility)
	{
		if (aPlayer.GetAttributes().agility >= myLock.agilityReq.attributeValue)
		{
			return true;
		}
	}
	if (aType == LockType::LockType_Strength)
	{
		if (aPlayer.GetAttributes().strength >= myLock.strengthReq.attributeValue)
		{
			return true;
		}
	}
	return false;
}

