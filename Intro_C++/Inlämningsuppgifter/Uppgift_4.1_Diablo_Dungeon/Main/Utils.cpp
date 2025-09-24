#include "Utils.h"
#include "GameEnums.h"
#include "GameConstants.h"
#include <iostream>
#include <random>

namespace Utils
{
	int ReadIntInRange(int aMinValue, int aMaxValue)
	{
		int value;
		while (true)
		{
			std::cin >> value;
			if (value >= aMinValue && value <= aMaxValue)
			{
				return value;
			}
			std::cin.clear();
			std::cin.ignore(GameConstants::CIN_IGNORE, '\n');
			std::cout << "Invalid. Enter a number between " << aMinValue << " and " << aMaxValue << ": ";
		}
	}

	int GenerateRandomNumber(int aMin, int aMaxValue)
	{
		std::random_device rd;
		std::mt19937 rng{rd()};
		std::uniform_int_distribution<int> dist(aMin, aMaxValue);
		return dist(rng);
	}

	Direction GetDoorPOSFromIndex(const int& index)
	{
		Direction doorPos = static_cast<Direction>(index);
		return doorPos;
	}

	int GetIndexFromDoorPOS(const Direction& aDoorPosition)
	{
		return static_cast<int>(aDoorPosition);
	}

	const char* PrintRedText(bool aStart)
	{
		if (aStart)
		{
			return "\x1b[31m";
		}
		return "\x1b[0m";
	}

	const char* LockTypeToString(const LockType& aLockType)
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
		case LockType::LockType_None:
			{
				return "none";
			}
		}
		return nullptr;
	}

	Direction Opposite(const Direction& d)
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
	}
}
