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
		std::mt19937 rng{ rd() };
		std::uniform_int_distribution<int> dist(aMin, aMaxValue);
		return dist(rng);
	}

	Direction GetDoorPOSFromIndex(const int& index)
	{
		Direction doorPos = static_cast<Direction>(index);
		return doorPos;
	}

	Position GetPosFromDirection(const Direction& aDirection)
	{
		switch (aDirection)
		{
		case Direction::West:
		{
			return { -1, 0 };
		}
		case Direction::North:
		{
			return { 0, 1 };
		}
		case Direction::East:
		{
			return { 1, 0 };
		}
		case Direction::South:
		{
			return { 0, -1 };
		}
		case Direction::None:
		{
			return { 0, 0 };
		}
		}
		return { 0, 0 };
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
		case LockType::None:
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
	}
	const char* GetColorCode(TextColor color, bool aStart)
	{
		if (!aStart)
			return "\x1b[0m"; // reset

		switch (color)
		{
		case TextColor::Red:
		{
			return "\x1b[31m"; // Red
		}
		case TextColor::Brown:
		{
			return "\x1b[33m"; // Brown-ish (ANSI only has yellow, looks like dark brown on some terms)
		}
		case TextColor::Silver:
		{
			return "\x1b[37m"; // White/grey
		}
		case TextColor::Gold:
		{
			return "\x1b[93m"; // Bright yellow (gold-like)
		}
		case TextColor::Magenta:
		{
			return "\x1b[35m"; // Magenta
		}
		default:
		{
			return "\x1b[0m"; // fallback reset
		}
		}
	}

	TextColor GetColorFromRarity(Rarity rarity) //none = red
	{
		return static_cast<TextColor>(rarity);
	}

	const char* RarityToString(Rarity rarity)
	{
		switch (rarity)
		{
		case Rarity::Bronze:
		{
			return "Bronze";
		}
		case Rarity::Silver:
		{
			return "Silver";
		}
		case Rarity::Gold:
		{
			return "Gold";
		}
		case Rarity::Legendary:
		{
			return "Legendary";
		}
		}
		return nullptr;
	}

}
