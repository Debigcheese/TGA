#include "Helpers.h"
#include "Structs.h"
#include <iostream>

namespace Helpers
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

	RandomGeneratorState::RandomGeneratorState(unsigned int seed)
		: rng(seed)
	{
	}


	int GenerateRandomNumber(int aMin, int aMaxValue)
	{
		std::uniform_int_distribution<int> dist(aMin, aMaxValue);
		return dist(GlobalRng.rng);
	}

	int RollDice()
	{
		return GenerateRandomNumber(DICE_MIN, DICE_MAX);
	}

	int ResultToIndex(const Result& aGameResult)
	{
		int index = static_cast<int>(aGameResult);
		return index;
	}

	void PrintIndexWithColor(const Color aColor, const int aIndex)
	{
		if (aColor == Color::Red)
		{
			std::cout << "\033[31m" << aIndex << "\033[0m";
			return;
		}
		std::cout << "\033[37m" << aIndex << "\033[0m";
	}

	void PrintBracketsWithColor(const Color aColor, const Side aSide)
	{
		char bracket = '[';
		if (aSide == Side::Right)
		{
			bracket = ']';
		}

		if (aColor == Color::Red)
		{
			std::cout << "\033[31m" << bracket << "\033[0m";
			return;
		}
		else if (aColor == Color::Black)
		{
			std::cout << "\033[37m" << bracket << "\033[0m";
			return;
		}
	}


	std::string myToString(int aValue)
	{
		if (aValue <= 0)
		{
			return std::string("0");
		}
		char buffer[MY_TO_STRING_BUFFER_SIZE] = {};
		int index = MY_TO_STRING_INDEX;
		int decimalBase = MY_TO_STRING_DECIMAL_BASE;

		buffer[index] = '\0';

		while (aValue > 0)
		{
			index--;
			buffer[index] = '0' + static_cast<char>((aValue % decimalBase));
			aValue /= decimalBase;
		}

		return std::string(&buffer[index]);
	}
}

//int randomCardIndex = dist(rng);
//char* randomCard = deck[randomCardIndex];
//
//if (randomCard != "-")
//{
//	return randomCard;
//}
