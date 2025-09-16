#include "Helpers.h"
#include "Structs.h"
#include <iostream>
#include <random>

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

	int GenerateRandomNumber(int aMin, int aMaxValue)
	{
		std::random_device rd;
		std::mt19937 rng{ rd() };
		std::uniform_int_distribution<int> dist(aMin, aMaxValue);
		return dist(rng);
	}

	int RollDice()
	{
		return GenerateRandomNumber(1, 6);
	}

	int TableToIndex(const TableOption& aTable)
	{
		int index = static_cast<int>(aTable);
		return (index - 1);
	}

	int ResultToIndex(const Result& aGameResult)
	{
		int index = static_cast<int>(aGameResult);
		return index;
	}

	RouletteColor GetColorFromIndex(const char aRouletteLayout[], const int aIndex)
	{
		if (aRouletteLayout[aIndex] == 'R')
		{
			return RouletteColor::RouletteColor_Red;
		}

		return RouletteColor::RouletteColor_Black;
	}

	void PrintIndexWithColor(const RouletteColor aColor, const int aIndex)
	{
		if (aColor == RouletteColor::RouletteColor_Red)
		{
			std::cout << "\033[31m" << aIndex << "\033[0m";
			return;
		}
		std::cout << "\033[37m" << aIndex << "\033[0m";
	}

	void PrintBracketsWithColor(const RouletteColor aColor, const Side aSide)
	{
		char bracket = '[';
		if (aSide == Side::Side_Right)
		{
			bracket = ']';
		}

		if (aColor == RouletteColor::RouletteColor_Red)
		{
			std::cout << "\033[31m" << bracket << "\033[0m";
			return;
		}
		else if (aColor == RouletteColor::RouletteColor_Black)
		{
			std::cout << "\033[37m" << bracket << "\033[0m";
			return;
		}

	}

	OddOrEven GetOddOrEvenFromIndex(const int aIndex)
	{
		if (aIndex != 0 && aIndex % 2 == 0)
		{
			return OddOrEven::OddOrEven_Even;
		}
		else if (aIndex != 0 && aIndex % 2 == 1)
		{
			return OddOrEven::OddOrEven_Odd;
		}
		return OddOrEven::OddOrEven_None;
	}

	Columns GetColumnFromIndex(const int aIndex)
	{
		if (aIndex % 3 == 1 && aIndex != 0)
		{
			return Columns::Columns_Left;
		}
		else if (aIndex % 3 == 2 && aIndex != 0)
		{
			return Columns::Columns_Middle;
		}
		else if (aIndex % 3 == 0 && aIndex != 0)
		{
			return Columns::Columns_Right;
		}
	}

	std::string GetStringFromRoulette(const RouletteBetPerType aBetPerType, const RouletteBetType aBetType)
	{
		std::string betTypeString = "";

		switch (aBetType)
		{
		case RouletteBetType::RouletteBetType_Straight:
		{
			betTypeString = myToString(aBetPerType.straight); // std::to_string(betPerType.straight);
			break;
		}
		case RouletteBetType::RouletteBetType_RedBlack:
		{
			if (aBetPerType.color == RouletteColor::RouletteColor_Red)
			{
				betTypeString = "Red";
			}
			else
			{
				betTypeString = "Black";
			}
			break;
		}
		case RouletteBetType::RouletteBetType_OddEven:
		{
			if (aBetPerType.oddOrEven == OddOrEven::OddOrEven_Odd)
			{
				betTypeString = "Odd";
			}
			else
			{
				betTypeString = "Even";
			}
			break;
		}
		case RouletteBetType::RouletteBetType_Column:
		{
			if (aBetPerType.column == Columns::Columns_Left)
			{
				betTypeString = "Left";
			}
			else if (aBetPerType.column == Columns::Columns_Middle)
			{
				betTypeString = "Middle";
			}
			else
			{
				betTypeString = "Right";
			}
			break;
		}
		default:
		{
			break;
		}
		}
		return betTypeString;
	}

	std::string myToString(int aValue)
	{
		if (aValue <= 0)
		{
			return std::string("0");
		}
		char buffer[CONSTANTS::MY_TO_STRING_BUFFER_SIZE] = {};
		int index = CONSTANTS::MY_TO_STRING_INDEX;
		int decimalBase = CONSTANTS::MY_TO_STRING_DECIMAL_BASE;

		buffer[index] = '\0';

		while (aValue > 0)
		{
			index--;
			buffer[index] = '0' + (aValue % decimalBase);
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