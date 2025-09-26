#pragma once
#include "Enums.h"
#include <string>
#include <random>

namespace Helpers
{
	struct RandomGeneratorState
	{
		std::mt19937 rng;

		RandomGeneratorState(unsigned int seed = std::random_device{}());
	};

	const int DICE_MIN = 1;
	const int DICE_MAX = 6;

	const int MY_TO_STRING_BUFFER_SIZE = 12;
	const int MY_TO_STRING_INDEX = 11;
	const int MY_TO_STRING_DECIMAL_BASE = 10;

	static RandomGeneratorState GlobalRng;

	int ReadIntInRange(int aMinValue, int aMaxValue);
	int GenerateRandomNumber(int aMin, int aMaxValue);
	int RollDice();
	int ResultToIndex(const Result& aGameResult);

	void PrintIndexWithColor(const Color aColor, const int aIndex);
	void PrintBracketsWithColor(const Color aColor, const Side aSide);

	std::string myToString(int aValue);
}
