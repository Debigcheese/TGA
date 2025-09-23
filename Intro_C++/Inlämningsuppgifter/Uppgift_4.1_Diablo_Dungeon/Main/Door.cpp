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
	case LockType::Unlocked:
	{
		return "Unlocked";
	}
	case LockType::Agility:
	{
		return "Agility";
	}
	case LockType::Strength:
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
		int lockChoice = Utils::ReadIntInRange(1, 3);

		switch (lockChoice)
		{
		case 1:
		{
			if (TryLockPick(aPlayer, LockType::Agility))
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
		case 2:
		{
			if (TryLockPick(aPlayer, LockType::Strength))
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
		case 3:
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

