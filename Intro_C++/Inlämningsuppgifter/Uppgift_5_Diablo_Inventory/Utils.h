#pragma once
#include "GameEnums.h"
#include "GameStructs.h"

#include <random>

namespace Utils
{
	struct RandomGeneratorState
	{
		std::mt19937 rng;

		RandomGeneratorState(unsigned int seed = std::random_device{}());
	};

	static RandomGeneratorState myRng;
	int ReadIntInRange(int aMinValue, int aMaxValue);
	int GenerateRandomNumber(int aMin, int aMaxValue);
	Direction GetDoorPOSFromIndex(const int& aIndex);
	Position GetPosFromDirection(const Direction& aDirection);
	int GetIndexFromDoorPOS(const Direction& aDoorPosition);
	const char* PrintRedText(bool aStart);
	const char* LockTypeToString(const LockType& aLockType);
	Direction Opposite(const Direction& d);
	const char* GetColorCode(TextColor color, bool aStart);
	TextColor GetColorFromRarity(Rarity rarity);
	const char* RarityToString(Rarity rarity);
	const char* GetPrefixSign(float aValue);
	std::vector<Rarity> GetRaritiesFromMax(Rarity aRarity);
}
