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
	: myMoneyEarned(0), roulette()
{
}
int RouletteGame::GetMoneyEarned() const
{
	return myMoneyEarned;
}
void RouletteGame::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

// ---------- Play Roulette ----------
void RouletteGame::PlayRoulette(Account& aAccount)
{
	while (true)
	{
		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";
		DrawRouletteBoard();
		PrintRouletteBet(RouletteBetType::RouletteBetType_None);

		int choiceMin = static_cast<int>(RouletteBetType::RouletteBetType_Straight);
		int choiceMax = static_cast<int>(RouletteBetType::RouletteBetType_Column);

		int choice = ReadIntInRange(choiceMin, choiceMax);
		roulette.betType = static_cast<RouletteBetType>(choice);

		system("cls");
		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";
		DrawRouletteBoard();
		int winningNumber = GenerateRandomNumber(0, ROULETTE_ARRAY_SIZE - ROULETTE_SIZE_TO_INDEX_OFFSET);

		switch (roulette.betType)
		{
		case RouletteBetType::RouletteBetType_Straight:
		{
			PrintRouletteBet(RouletteBetType::RouletteBetType_Straight);
			int choiceStraight = ReadIntInRange(0, ROULETTE_ARRAY_SIZE - ROULETTE_SIZE_TO_INDEX_OFFSET);
			roulette.betPerType.straight = choiceStraight;
			roulette.winningType.straight = winningNumber;
			break;
		}
		case RouletteBetType::RouletteBetType_RedBlack:
		{
			PrintRouletteBet(RouletteBetType::RouletteBetType_RedBlack);
			int colorIndexMin = static_cast<int>(RouletteColor::RouletteColor_Red);
			int colorIndexMax = static_cast<int>(RouletteColor::RouletteColor_Black);
			int choiceColor = ReadIntInRange(colorIndexMin, colorIndexMax);

			roulette.betPerType.color = static_cast<RouletteColor>(choiceColor);
			roulette.winningType.color = GetColorFromIndex(roulette.rouletteLayout, winningNumber);
			break;
		}
		case RouletteBetType::RouletteBetType_OddEven:
		{
			PrintRouletteBet(RouletteBetType::RouletteBetType_OddEven);
			int OddOrEvenMin = static_cast<int>(OddOrEven::OddOrEven_Odd);
			int OddOrEvenMax = static_cast<int>(OddOrEven::OddOrEven_Even);
			int choiceOddOrEven = ReadIntInRange(OddOrEvenMin, OddOrEvenMax);

			roulette.betPerType.oddOrEven = static_cast<OddOrEven>(choiceOddOrEven);
			roulette.winningType.oddOrEven = GetOddOrEvenFromIndex(winningNumber);
			break;
		}
		case RouletteBetType::RouletteBetType_Column:
		{
			PrintRouletteBet(RouletteBetType::RouletteBetType_Column);
			int colMin = static_cast<int>(Columns::Columns_Left);
			int colMax = static_cast<int>(Columns::Columns_Right);
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

		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";
		DrawRouletteBoard();
		std::cout << "\n";

		std::cout << "Ball landed on: " << winningNumber << "\n\n";
		std::cout << "Your guess: " << roulette.betTypeString << "\n";
		std::cout << "Winning guess: " << roulette.winningBetTypeString << "\n\n";

		if (RouletteResult())
		{
			myMoneyEarned += Casino::Payout(aAccount, GetRoulettePayoutAmount());
			Casino::UpdateStats(true);
		}
		else
		{
			myMoneyEarned -= Casino::DeductBet(aAccount);
			Casino::UpdateStats(false);
		}
		system("pause");
		break;
	}
}

//Roulette class specific functions
void RouletteGame::PrintRouletteBet(const RouletteBetType& aBetType) const
{
	switch (aBetType)
	{
	case RouletteBetType::RouletteBetType_None:
	{
		std::cout << "\n";
		std::cout << "Place your bets! \n";
		std::cout << "(1) Straight  \n";
		std::cout << "(2) Red/Black  \n";
		std::cout << "(3) Odd/Even:  \n";
		std::cout << "(4) Column:    \n";
		break;
	}
	case RouletteBetType::RouletteBetType_Straight:
	{
		std::cout << "\nPick your number!\n";
		break;
	}
	case RouletteBetType::RouletteBetType_RedBlack:
	{
		std::cout << "\nChoose Red or Black! \n";
		std::cout << "Red   (1)\n";
		std::cout << "Black (2)\n";
		break;
	}
	case RouletteBetType::RouletteBetType_OddEven:
	{
		std::cout << "\nChoose odd or even! \n";
		std::cout << "Odd  (1)\n";
		std::cout << "Even (2)\n";
		break;
	}
	case RouletteBetType::RouletteBetType_Column:
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
void RouletteGame::DrawRouletteBoard() const
{
	for (int i = 0; i < ROULETTE_ARRAY_SIZE; i++)
	{
		if (i == 0)
		{
			std::cout << "    [" << roulette.rouletteLayout[i] << "]\n";
		}
		else
		{
			if ((i % CONSTANTS::COLUMN_TOTAL_AMOUNT == static_cast<int>(Columns::Columns_Left)) && i < ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD)
			{
				std::cout << " ";
			}
			RouletteColor indexColor = GetColorFromIndex(roulette.rouletteLayout, i);
			PrintBracketsWithColor(indexColor, Side::Side_Left);
			PrintIndexWithColor(indexColor, i);
			PrintBracketsWithColor(indexColor, Side::Side_Right);

			if (i % CONSTANTS::COLUMN_TOTAL_AMOUNT == 0)
			{
				std::cout << "\n";
			}

		}
	}
}
bool RouletteGame::RouletteResult() const
{
	switch (roulette.betType)
	{
	case RouletteBetType::RouletteBetType_Straight:
	{
		if (roulette.betPerType.straight == roulette.winningType.straight)
		{
			return true;
		}
		break;
	}
	case RouletteBetType::RouletteBetType_RedBlack:
	{
		if (roulette.betPerType.color == roulette.winningType.color)
		{
			return true;
		}
		break;
	}
	case RouletteBetType::RouletteBetType_OddEven:
	{
		if (roulette.betPerType.oddOrEven == roulette.winningType.oddOrEven)
		{
			return true;
		}
		break;
	}
	case RouletteBetType::RouletteBetType_Column:
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
int RouletteGame::GetRoulettePayoutAmount() const
{
	int payoutAmount = 0;
	switch (roulette.betType)
	{
	case RouletteBetType::RouletteBetType_Straight:
	{
		payoutAmount = BET_MULTI_ROULETTE_STRAIGHT;
		break;
	}
	case RouletteBetType::RouletteBetType_RedBlack:
	{
		payoutAmount = BET_MULTI_ROULETTE_COLOR;
		break;
	}
	case RouletteBetType::RouletteBetType_OddEven:
	{
		payoutAmount = BET_MULTI_ROULETTE_ODDOREVEN;
		break;
	}
	case RouletteBetType::RouletteBetType_Column:
	{
		payoutAmount = BET_MULTI_ROULETTE_COLUMN;
		break;
	}
	default:
	{
		break;
	}
	}
	return payoutAmount;
}
