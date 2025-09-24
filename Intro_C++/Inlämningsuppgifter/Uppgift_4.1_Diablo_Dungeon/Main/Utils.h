#pragma once
#include "GameEnums.h"

namespace Utils
{
	int ReadIntInRange(int aMinValue, int aMaxValue);
	int GenerateRandomNumber(int aMin, int aMaxValue);
	Direction GetDoorPOSFromIndex(const int& aIndex);
	int GetIndexFromDoorPOS(const Direction& aDoorPosition);
	const char* PrintRedText(bool aStart);
	const char* LockTypeToString(const LockType& aLockType);
	Direction Opposite(const Direction& d);
}
