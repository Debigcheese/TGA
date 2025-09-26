#include "Casino.h"
#include "RouletteGame.h"
#include "Helpers.h"
#include "Print.h"

#include "Structs.h"
#include "Enums.h"

#include <iostream>

using namespace Helpers;
using namespace Print;

const char RouletteGame::ROULETTE_LAYOUT[ROULETTE_ARRAY_SIZE] = {
	'0',
	'R', 'B', 'R',
	'B', 'R', 'B',
	'R', 'B', 'R',
	'B', 'B', 'R',

	'B', 'R', 'B',
	'R', 'B', 'R',
	'R', 'B', 'R',
	'B', 'R', 'B',

	'R', 'B', 'R',
	'B', 'B', 'R',
	'B', 'R', 'B',
	'R', 'B', 'R'
};


RouletteGame::RouletteGame()
	: myMoneyEarned(0),
	  myRoulette()
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
		PrintRouletteBet(RouletteBetType::None);

		int choiceMin = static_cast<int>(RouletteBetType::Straight);
		int choiceMax = static_cast<int>(RouletteBetType::Column);

		int choice = ReadIntInRange(choiceMin, choiceMax);
		myRoulette.betType = static_cast<RouletteBetType>(choice);

		system("cls");
		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";
		DrawRouletteBoard();
		int rouletteArraySize = ROULETTE_ARRAY_SIZE;
		int winningNumber = GenerateRandomNumber(0, rouletteArraySize - ROULETTE_SIZE_TO_INDEX_OFFSET);

		switch (myRoulette.betType)
		{
			case RouletteBetType::Straight:
			{
				PrintRouletteBet(RouletteBetType::Straight);
				int choiceStraight = ReadIntInRange(0, rouletteArraySize - ROULETTE_SIZE_TO_INDEX_OFFSET);
				myRoulette.betPerType.straight = choiceStraight;
				myRoulette.winningType.straight = winningNumber;
				break;
			}
			case RouletteBetType::RedBlack:
			{
				PrintRouletteBet(RouletteBetType::RedBlack);
				int colorIndexMin = static_cast<int>(Color::Red);
				int colorIndexMax = static_cast<int>(Color::Black);
				int choiceColor = ReadIntInRange(colorIndexMin, colorIndexMax);

				myRoulette.betPerType.color = static_cast<Color>(choiceColor);
				myRoulette.winningType.color = GetColorFromIndex(winningNumber);
				break;
			}
			case RouletteBetType::OddEven:
			{
				PrintRouletteBet(RouletteBetType::OddEven);
				int OddOrEvenMin = static_cast<int>(OddOrEven::Odd);
				int OddOrEvenMax = static_cast<int>(OddOrEven::Even);
				int choiceOddOrEven = ReadIntInRange(OddOrEvenMin, OddOrEvenMax);

				myRoulette.betPerType.oddOrEven = static_cast<OddOrEven>(choiceOddOrEven);
				myRoulette.winningType.oddOrEven = GetOddOrEvenFromIndex(winningNumber);
				break;
			}
			case RouletteBetType::Column:
			{
				PrintRouletteBet(RouletteBetType::Column);
				int colMin = static_cast<int>(Columns::Left);
				int colMax = static_cast<int>(Columns::Right);
				int choiceColumn = ReadIntInRange(colMin, colMax);

				myRoulette.betPerType.column = static_cast<Columns>(choiceColumn);
				myRoulette.winningType.column = GetColumnFromIndex(winningNumber);
				break;
			}
			default:
			{
				break;
			}
		}

		myRoulette.betTypeString = GetStringFromRoulette(myRoulette.betPerType);
		myRoulette.winningBetTypeString = GetStringFromRoulette(myRoulette.winningType);

		std::cout << "\nYou betted on: " << myRoulette.betTypeString << "\n";
		std::cout << "Ball is rolling...\n";
		system("pause");

		system("cls");

		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";
		DrawRouletteBoard();
		std::cout << "\n";

		std::cout << "Ball landed on: " << winningNumber << "\n\n";
		std::cout << "Your guess: " << myRoulette.betTypeString << "\n";
		std::cout << "Winning guess: " << myRoulette.winningBetTypeString << "\n\n";

		if (GetRouletteResult())
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

void RouletteGame::DrawRouletteBoard() const
{
	for (int i = 0; i < ROULETTE_ARRAY_SIZE; i++)
	{
		if (i == 0)
		{
			std::cout << "    [" << ROULETTE_LAYOUT[i] << "]\n";
		}
		else
		{
			if ((i % COLUMN_TOTAL_AMOUNT == static_cast<int>(Columns::Left)) && i <
				ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD)
			{
				std::cout << " ";
			}
			Color indexColor = GetColorFromIndex(i);
			PrintBracketsWithColor(indexColor, Side::Left);
			PrintIndexWithColor(indexColor, i);
			PrintBracketsWithColor(indexColor, Side::Right);

			if (i % COLUMN_TOTAL_AMOUNT == 0)
			{
				std::cout << "\n";
			}
		}
	}
}

bool RouletteGame::GetRouletteResult() const
{
	switch (myRoulette.betType)
	{
		case RouletteBetType::Straight:
		{
			if (myRoulette.betPerType.straight == myRoulette.winningType.straight)
			{
				return true;
			}
			break;
		}
		case RouletteBetType::RedBlack:
		{
			if (myRoulette.betPerType.color == myRoulette.winningType.color)
			{
				return true;
			}
			break;
		}
		case RouletteBetType::OddEven:
		{
			if (myRoulette.betPerType.oddOrEven == myRoulette.winningType.oddOrEven)
			{
				return true;
			}
			break;
		}
		case RouletteBetType::Column:
		{
			if (myRoulette.betPerType.column == myRoulette.winningType.column)
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
	switch (myRoulette.betType)
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
	return payoutAmount;
}

std::string RouletteGame::GetStringFromRoulette(const RouletteBetPerType aBetPerType) const
{
	switch (myRoulette.betType)
	{
		case RouletteBetType::Straight:
		{
			return myToString(aBetPerType.straight); // std::to_string(betPerType.straight);
		}
		case RouletteBetType::RedBlack:
		{
			if (aBetPerType.color == Color::Red)
			{
				return "Red";
			}
			if (aBetPerType.color == Color::Black)
			{
				return "Black";
			}
			return "Green";
		}
		case RouletteBetType::OddEven:
		{
			if (aBetPerType.oddOrEven == OddOrEven::Odd)
			{
				return "Odd";
			}
			if (aBetPerType.oddOrEven == OddOrEven::Even)
			{
				return "Even";
			}
			return "0";
		}
		case RouletteBetType::Column:
		{
			if (aBetPerType.column == Columns::Left)
			{
				return "Left";
			}
			if (aBetPerType.column == Columns::Middle)
			{
				return "Middle";
			}
			if (aBetPerType.column == Columns::Right)
			{
				return "Right";
			}
			return "0";
		}
		default:
		{
			return myRoulette.betTypeString;
		}
	}
}


Color RouletteGame::GetColorFromIndex(const int aIndex) const
{
	if (aIndex == ZERO_INDEX)
	{
		return Color::Green;
	}
	if (ROULETTE_LAYOUT[aIndex] == 'R')
	{
		return Color::Red;
	}
	return Color::Black;
}

OddOrEven RouletteGame::GetOddOrEvenFromIndex(const int aIndex) const
{
	if (aIndex == ZERO_INDEX)
	{
		return OddOrEven::None;
	}
	if (aIndex % EVEN_DIVISOR == REMAINDER_EVEN)
	{
		return OddOrEven::Even;
	}
	return OddOrEven::Odd;
}

Columns RouletteGame::GetColumnFromIndex(const int aIndex) const
{
	if (aIndex == ZERO_INDEX)
	{
		return Columns::None;
	}
	if (aIndex % COLUMN_TOTAL_AMOUNT == COLUMN_LEFT_REMAINDER)
	{
		return Columns::Left;
	}
	if (aIndex % COLUMN_TOTAL_AMOUNT == COLUMN_MIDDLE_REMAINDER)
	{
		return Columns::Middle;
	}

	return Columns::Right;
}
