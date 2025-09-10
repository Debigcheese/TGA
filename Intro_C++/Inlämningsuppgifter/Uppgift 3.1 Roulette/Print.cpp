#include "Print.h"
#include "TableFunctions.h"
#include "Helpers.h"

#include <iostream>

namespace Print
{

	// ---------- Print to console ----------
	void ShowIntro(const Account& account)
	{
		std::cout << "Welcome to the funky basement casino!\n";
		std::cout << "You start with " << account.money << " kr.\n\n";
		system("pause");
		system("cls");
	}

	void ShowPersonalDetails(const Account& account)
	{
		system("cls");
		std::cout << "Wallet: " << account.money << " kr \nCurrent bet: " << account.bet << " kr\n";
	}

	void ShowOptions(const Table& table)
	{
		if (table.currentTable == TableOption::Menu)
		{
			std::cout
				<< "\n<--- Main Menu --->\n"
				<< "1) Guess The Sum\n"
				<< "2) Odd or Even\n"
				<< "3) Spin The Wheel\n"
				<< "4) Higher or Lower\n"
				<< "5) Roulette\n"
				<< "6) Show Stats\n"
				<< "7) Leave casino\n"
				<< "Choice: ";
		}
		else if (table.currentTable == TableOption::GuessingGame)
		{
			std::cout
				<< "\n=== Table: Guess The Sum ===\n"
				<< "1) Play a round\n"
				<< "2) Change bet\n"
				<< "3) Show rules\n"
				<< "4) Leave table\n"
				<< "Choice: ";
		}
		else if (table.currentTable == TableOption::OddOrEven)
		{
			std::cout
				<< "\n=== Table: Odd or Even ===\n"
				<< "1) Play a round\n"
				<< "2) Change bet\n"
				<< "3) Show rules\n"
				<< "4) Leave table\n"
				<< "Choice: ";
		}
		else if (table.currentTable == TableOption::SpinTheWheel)
		{
			std::cout
				<< "\n=== Table: Spin The Wheel ===\n"
				<< "1) Play a round\n"
				<< "2) Change bet\n"
				<< "3) Show rules\n"
				<< "4) Leave table\n"
				<< "Choice: ";
		}
		else if (table.currentTable == TableOption::HighOrLow)
		{
			std::cout
				<< "\n=== Table: Higher or Lower ===\n"
				<< "1) Play a round\n"
				<< "2) Change bet\n"
				<< "3) Show rules\n"
				<< "4) Leave table\n"
				<< "Choice: ";
		}
		else if (table.currentTable == TableOption::Roulette)
		{
			std::cout
				<< "\n=== Table: Roulette ===\n"
				<< "1) Play a round\n"
				<< "2) Change bet\n"
				<< "3) Show rules\n"
				<< "4) Leave table\n"
				<< "Choice: ";
		}


	}

	void ShowRules(const Table& table)
	{
		if (table.currentTable == TableOption::GuessingGame)
		{
			std::cout
				<< "\n--- Rules: Guess The Sum ---\n"
				<< "Guess the sum of two dice (2-12).\n"
				<< "Two dice are rolled and shown, plus the total.\n"
				<< "Wrong guess: you lose your bet.\n"
				<< "Payout: 5x on correct guess.\n";
		}
		else if (table.currentTable == TableOption::OddOrEven)
		{
			std::cout
				<< "\n--- Rules: Odd or Even ---\n"
				<< "Pick Odd (1) or Even (2). Two dice are rolled and shown.\n"
				<< "Win if both dice are odd when you picked Odd, or both even when you picked Even.\n"
				<< "Mixed parity means the house wins. Sum does not matter.\n"
				<< "Payout: 2x on win, otherwise you lose your bet.\n";
		}
		else if (table.currentTable == TableOption::SpinTheWheel)
		{
			std::cout
				<< "\n--- Rules: Spin The Wheel ---\n"
				<< "The wheel shows 3 random symbols, chosen from 6 possible ones.\n"
				<< "Win a small prize if two symbols match and the third is different.\n"
				<< "Win a large prize if all three symbols match, JACKPOT!\n"
				<< "If all three symbols are different the house wins and you lose your bet.\n"
				<< "Payout: 2x for two of a kind, 40x for three of a kind.\n";
		}
		else if (table.currentTable == TableOption::HighOrLow)
		{
			std::cout
				<< "\n--- Rules: Higher or Lower ---\n"
				<< "You play with a deck containing one of each card (2 through Ace).\n"
				<< "A starting card is drawn. You must guess if the next card will be higher or lower.\n"
				<< "If your guess is correct, you score a point. If not, you dont get a point.\n"
				<< "This repeats until the deck is empty.\n"
				<< "Win if you have enough points by the end of the deck.\n"
				<< "Lose if you fail to reach the required points.\n"
				<< "Payout: 2x if you win.\n";
		}
		system("pause");
	}

	void ShowStats(const Table& table)
	{
		std::cout << "\nYour five most recent games: \n";

		const int statArrSize = sizeof(table.statArr) / sizeof(int);

		for (int i = 0; i < statArrSize; i++)
		{
			std::cout << i + 1 << ": ";

			if (table.statArr[i] == Helpers::ResultToIndex(Result::Loss))
			{
				std::cout << "Loss";
			}
			else if (table.statArr[i] == Helpers::ResultToIndex(Result::Win))
			{
				std::cout << "Win";
			}
			else
			{
				std::cout << "-";

			}
			std::cout << "\n";
		}
	}

	void PrintRouletteType(const Roulette& roulette)
	{


	}

	void PrintRouletteBet()
	{
		std::cout << "\n";
		std::cout << "Place your bets! \n";
		std::cout << "(1) Straight  \n";
		std::cout << "(2) Red/Black  \n";
		std::cout << "(3) Odd/Even:  \n";
		std::cout << "(4) Column:    \n";
		std::cout << "Choice: ";
	}
}