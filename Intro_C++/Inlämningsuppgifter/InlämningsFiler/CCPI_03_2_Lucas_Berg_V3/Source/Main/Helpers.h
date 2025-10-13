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

	//constants
	const int DICE_MIN = 1;
	const int DICE_MAX = 6;
	
	const int TO_STRING_BUFFER_SIZE = 12;
	const int TO_STRING_INDEX = 11;
	const int TO_STRING_DECIMAL_BASE = 10;
	const int CIN_IGNORE_MAX = 10000;

	const int EVEN_DIVISOR = 2;
	const int REMAINDER_ODD = 1;
	const int REMAINDER_EVEN = 0;

	const int ZERO_INDEX = 0;
	
	static RandomGeneratorState GlobalRng;

	int ReadIntInRange(int aMinValue, int aMaxValue);
	int GenerateRandomNumber(int aMin, int aMaxValue);

	int ResultToIndex(const Result& aGameResult);

	void PrintIndexWithColor(const Color aColor, const int aIndex);
	void PrintBracketsWithColor(const Color aColor, const Side aSide);
	std::string myToString(int aValue);


}
