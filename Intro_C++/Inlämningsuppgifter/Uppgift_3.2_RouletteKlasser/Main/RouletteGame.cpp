#include "Casino.h"
#include "RouletteGame.h"
#include "Helpers.h"
#include "Print.h"
#include "CONSTANTS.h"

#include "Structs.h"
#include "Enums.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

RouletteGame::RouletteGame()
{
}

RouletteGame::RouletteGame(int aMoneyEarned) : myMoneyEarned(aMoneyEarned) {}

int RouletteGame::GetMoneyEarned()
{
	return myMoneyEarned;
}

void RouletteGame::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}


// ---------- Play Roulette ----------
void RouletteGame::PlayRoulette(Account& account, Table& table)
{
	Roulette roulette = {};
	while (true)
	{
		Print::ShowPersonalDetails(account);
		std::cout << "\n";
		DrawRouletteBoard(roulette);
		PrintRouletteBet(RouletteBetType::None);

		int choiceMin = static_cast<int>(RouletteBetType::Straight);
		int choiceMax = static_cast<int>(RouletteBetType::Column);

		int choice = ReadIntInRange(choiceMin, choiceMax);
		roulette.betType = static_cast<RouletteBetType>(choice);

		system("cls");
		Print::ShowPersonalDetails(account);
		std::cout << "\n";
		DrawRouletteBoard(roulette);
		int winningNumber = GenerateRandomNumber(0, ROULETTE_ARRAY_SIZE - 1);

		switch (roulette.betType)
		{
		case RouletteBetType::Straight:
		{
			PrintRouletteBet(RouletteBetType::Straight);
			int choiceStraight = ReadIntInRange(0, ROULETTE_ARRAY_SIZE - 1);
			roulette.betPerType.straight = choiceStraight;
			roulette.winningType.straight = winningNumber;
			break;
		}
		case RouletteBetType::RedBlack:
		{
			PrintRouletteBet(RouletteBetType::RedBlack);
			int colorIndexMin = static_cast<int>(RouletteColor::Red);
			int colorIndexMax = static_cast<int>(RouletteColor::Black);
			int choiceColor = ReadIntInRange(colorIndexMin, colorIndexMax);

			roulette.betPerType.color = static_cast<RouletteColor>(choiceColor);
			roulette.winningType.color = GetColorFromIndex(roulette.rouletteLayout, winningNumber);
			break;
		}
		case RouletteBetType::OddEven:
		{
			PrintRouletteBet(RouletteBetType::OddEven);
			int OddOrEvenMin = static_cast<int>(OddOrEven::Odd);
			int OddOrEvenMax = static_cast<int>(OddOrEven::Even);
			int choiceOddOrEven = ReadIntInRange(OddOrEvenMin, OddOrEvenMax);

			roulette.betPerType.OddOrEven = static_cast<OddOrEven>(choiceOddOrEven);
			roulette.winningType.OddOrEven = GetOddOrEvenFromIndex(winningNumber);
			break;
		}
		case RouletteBetType::Column:
		{
			PrintRouletteBet(RouletteBetType::Column);
			int colMin = static_cast<int>(Columns::Left);
			int colMax = static_cast<int>(Columns::Right);
			int choiceColumn = ReadIntInRange(colMin, colMax);

			roulette.betPerType.column = static_cast<Columns>(choiceColumn);
			roulette.winningType.column = GetColumnFromIndex(winningNumber);
			break;
		}
		default:
		{
			break;
		}
		}

		roulette.betTypeString = GetStringFromRoulette(roulette.betPerType, roulette.betType);
		roulette.winningBetTypeString = GetStringFromRoulette(roulette.winningType, roulette.betType);

		std::cout << "\nYou betted on: " << roulette.betTypeString << "\n";
		std::cout << "Ball is rolling...\n";
		system("pause");

		system("cls");

		Print::ShowPersonalDetails(account);
		std::cout << "\n";
		DrawRouletteBoard(roulette);
		std::cout << "\n";

		std::cout << "Ball landed on: " << winningNumber << "\n\n";
		std::cout << "Your guess: " << roulette.betTypeString << "\n";
		std::cout << "Winning guess: " << roulette.winningBetTypeString << "\n\n";

		if (RouletteResult(roulette))
		{
			Casino::Payout(account, table, RouletteBetPayout(roulette));
			Casino::UpdateStats(table, true);

		}
		else
		{
			account.money -= account.bet;
			table.moneyArr[TableToIndex(TableOption::Roulette)] -= account.bet;
			std::cout << "House wins. You lose " << account.bet << " kr.\n";
			Casino::UpdateStats(table, false);
		}
		system("pause");
		break;

		// setup rules. make it so you go back to play round table menu after a round.
	}
}

//Roulette class specific functions
void RouletteGame::PrintRouletteBet(const RouletteBetType& betType)
{
	switch (betType)
	{
	case RouletteBetType::None:
	{
		std::cout << "\n";
		std::cout << "Place your bets! \n";
		std::cout << "(1) Straight  \n";
		std::cout << "(2) Red/Black  \n";
		std::cout << "(3) Odd/Even:  \n";
		std::cout << "(4) Column:    \n";
		break;
	}
	case RouletteBetType::Straight:
	{
		std::cout << "\nPick your number!\n";
		break;
	}
	case RouletteBetType::RedBlack:
	{
		std::cout << "\nChoose Red or Black! \n";
		std::cout << "Red   (1)\n";
		std::cout << "Black (2)\n";
		break;
	}
	case RouletteBetType::OddEven:
	{
		std::cout << "\nChoose odd or even! \n";
		std::cout << "Odd  (1)\n";
		std::cout << "Even (2)\n";
		break;
	}
	case RouletteBetType::Column:
	{
		std::cout << "\nChoose column! \n";
		std::cout << "Left Column   (1)\n";
		std::cout << "Middle Column (2)\n";
		std::cout << "Right Column  (3)\n";
		break;
	}
	default:
	{
		break;
	}
	}
	std::cout << "Choice: ";


}
void RouletteGame::DrawRouletteBoard(const Roulette& roulette)
{
	for (int i = 0; i < ROULETTE_ARRAY_SIZE; i++)
	{
		if (i == 0)
		{
			std::cout << "    [" << roulette.rouletteLayout[i] << "]\n";
		}
		else
		{
			if ((i % CONSTANTS::COLUMN_TOTAL_AMOUNT == static_cast<int>(Columns::Left)) && i < ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD)
			{
				std::cout << " ";
			}
			//if ((i % 3 == 0) && i < 10)
			//{
			//	std::cout << "  ";
			//}
			RouletteColor indexColor = GetColorFromIndex(roulette.rouletteLayout, i);
			PrintBracketsWithColor(indexColor, Side::Left);
			PrintIndexWithColor(indexColor, i);
			PrintBracketsWithColor(indexColor, Side::Right);

			if (i % CONSTANTS::COLUMN_TOTAL_AMOUNT == 0)
			{
				std::cout << "\n";
			}

		}
	}
}
bool RouletteGame::RouletteResult(const Roulette& roulette)
{
	switch (roulette.betType)
	{
	case RouletteBetType::Straight:
	{
		if (roulette.betPerType.straight == roulette.winningType.straight)
		{
			return true;
		}
		break;
	}
	case RouletteBetType::RedBlack:
	{
		if (roulette.betPerType.color == roulette.winningType.color)
		{
			return true;
		}
		break;
	}
	case RouletteBetType::OddEven:
	{
		if (roulette.betPerType.OddOrEven == roulette.winningType.OddOrEven)
		{
			return true;
		}
		break;
	}
	case RouletteBetType::Column:
	{
		if (roulette.betPerType.column == roulette.winningType.column)
		{
			return true;
		}
		break;
	}
	default:
	{
		break;
	}
	}
	return false;
}
int RouletteGame::RouletteBetPayout(const Roulette& roulette)
{
	int payoutAmount = 0;
	switch (roulette.betType)
	{
	case RouletteBetType::Straight:
	{
		payoutAmount = BET_MULTI_ROULETTE_STRAIGHT;
		break;
	}
	case RouletteBetType::RedBlack:
	{
		payoutAmount = BET_MULTI_ROULETTE_COLOR;
		break;
	}
	case RouletteBetType::OddEven:
	{
		payoutAmount = BET_MULTI_ROULETTE_ODDOREVEN;
		break;
	}
	case RouletteBetType::Column:
	{
		payoutAmount = BET_MULTI_ROULETTE_COLUMN;
		break;
	}
	default:
	{
		break;
	}
	}
}
