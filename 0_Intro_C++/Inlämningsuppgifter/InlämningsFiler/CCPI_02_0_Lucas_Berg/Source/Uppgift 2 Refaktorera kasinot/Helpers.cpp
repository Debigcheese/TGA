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
		std::random_device rd;
		std::mt19937 rng{ rd() };
		std::uniform_int_distribution<int> dist(CONSTANTS::DICE_MIN, CONSTANTS::DICE_MAX);
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

}

//int randomCardIndex = dist(rng);
//char* randomCard = deck[randomCardIndex];
//
//if (randomCard != "-")
//{
//	return randomCard;
//}