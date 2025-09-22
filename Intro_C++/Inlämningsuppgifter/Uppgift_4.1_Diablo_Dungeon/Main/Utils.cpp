#include "Utils.h"
#include "GameEnums.h"
#include <string>
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
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid. Enter a number between " << aMinValue << " and " << aMaxValue << ": ";
		}
	}
	int GenerateRandomNumber(int aMin, int aMaxValue)
	{
		std::random_device rd;
		std::mt19937 rng{ rd() };
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
	const char* EnemyTypeToString(const EnemyType aType)
	{
		switch (aType)
		{
		case EnemyType::EnemyType_None:
		{
			return "None";
		}
		case EnemyType::EnemyType_Bat:
		{
			return "Bat";
		}
		case EnemyType::EnemyType_Skeleton:
		{
			return "Skeleton";
		}
		case EnemyType::EnemyType_Undead:
		{
			return "Undead";
		}
		case EnemyType::EnemyType_Beast:
		{
			return "Beast";
		}
		case EnemyType::EnemyType_Humanoid:
		{
			return "Humanoid";
		}
		case EnemyType::EnemyType_Elemental:
		{
			return "Elemental";
		}
		case EnemyType::EnemyType_Demon:
		{
			return "Demon";
		}
		}
		return "Unknown";
	}

	const char* PrintRedText(bool aStart)
	{
		if (aStart)
		{
			return "\x1b[31m";

		}
		return "\x1b[0m";
	}

}

