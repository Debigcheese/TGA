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

	int TableToIndex(const TableOption& table)
	{
		int index = static_cast<int>(table);
		return (index - 1);
	}

	int ResultToIndex(const Result& gameResult)
	{
		int index = static_cast<int>(gameResult);
		return index;
	}

	RouletteColor GetColorFromIndex(const char rouletteLayout[], const int i)
	{
		if (rouletteLayout[i] == 'R')
		{
			return RouletteColor::Red;
		}

		return RouletteColor::Black;
	}

	void PrintIndexWithColor(const RouletteColor color, const int index)
	{
		if (color == RouletteColor::Red)
		{
			std::cout << "\033[31m" << index << "\033[0m";
			return;
		}
		std::cout << "\033[37m" << index << "\033[0m";
	}

	void PrintBracketsWithColor(const RouletteColor color, const Side side)
	{
		char bracket = '[';
		if (side == Side::Right)
		{
			bracket = ']';
		}

		if (color == RouletteColor::Red)
		{
			std::cout << "\033[31m" << bracket << "\033[0m";
			return;
		}
		else if (color == RouletteColor::Black)
		{
			std::cout << "\033[37m" << bracket << "\033[0m";
			return;
		}

	}

	OddOrEven GetOddOrEvenFromIndex(const int index)
	{
		if (index != 0 && index % 2 == 0)
		{
			return OddOrEven::Even;
		}
		else if (index != 0 && index % 2 == 1)
		{
			return OddOrEven::Odd;
		}
		return OddOrEven::None;
	}

	Columns GetColumnFromIndex(const int index)
	{
		if (index % 3 == 1 && index != 0)
		{
			return Columns::Left;
		}
		else if (index % 3 == 2 && index != 0)
		{
			return Columns::Middle;
		}
		else if (index % 3 == 0 && index != 0)
		{
			return Columns::Right;
		}
	}

	std::string GetStringFromRoulette(const RouletteBetPerType betPerType, const RouletteBetType betType)
	{
		std::string betTypeString = "";

		switch (betType)
		{
		case RouletteBetType::Straight:
		{
			betTypeString = myToString(betPerType.straight); // std::to_string(betPerType.straight);
			break;
		}
		case RouletteBetType::RedBlack:
		{
			if (betPerType.color == RouletteColor::Red)
			{
				betTypeString = "Red";
			}
			else
			{
				betTypeString = "Black";
			}
			break;
		}
		case RouletteBetType::OddEven:
		{
			if (betPerType.OddOrEven == OddOrEven::Odd)
			{
				betTypeString = "Odd";
			}
			else
			{
				betTypeString = "Even";
			}
			break;
		}
		case RouletteBetType::Column:
		{
			if (betPerType.column == Columns::Left)
			{
				betTypeString = "Left";
			}
			else if (betPerType.column == Columns::Middle)
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

	std::string myToString(int value)
	{
		if (value <= 0)
		{
			return std::string("0");
		}
		char buffer[CONSTANTS::MY_TO_STRING_BUFFER_SIZE] = {};
		int index = CONSTANTS::MY_TO_STRING_INDEX;
		int decimalBase = CONSTANTS::MY_TO_STRING_DECIMAL_BASE;
		buffer[index] = '\0';

		while (value > 0)
		{
			index--;
			buffer[index] = '0' + (value % decimalBase);
			value /= decimalBase;
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