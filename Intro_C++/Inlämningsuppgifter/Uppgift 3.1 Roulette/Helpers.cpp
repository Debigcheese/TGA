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

	int RollDice()
	{
		Dice dice = {};
		std::random_device rd;
		std::mt19937 rng{ rd() };
		std::uniform_int_distribution<int> dist(dice.diceMin, dice.diceMax);
		return dist(rng);
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

	void PrintIndexWithColor(const RouletteColor color, const int i)
	{
		if (color == RouletteColor::Red)
		{
			std::cout << "\033[31m" << i << "\033[0m";
			return;
		}
		std::cout << "\033[37m" << i << "\033[0m";
	}

	void PrintBracketsWithColor(const RouletteColor color, const int side)
	{
		char bracket = '[';
		if (side == 1)
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

}

//int randomCardIndex = dist(rng);
//char* randomCard = deck[randomCardIndex];
//
//if (randomCard != "-")
//{
//	return randomCard;
//}