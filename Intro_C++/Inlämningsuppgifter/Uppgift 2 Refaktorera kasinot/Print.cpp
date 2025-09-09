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
		std::cout << "You start with $" << account.money << ".\n\n";
		system("pause");
		system("cls");
	}

	void ShowPersonalDetails(const Account& account)
	{
		system("cls");
		std::cout << "Wallet: " << account.money << " kr. \nCurrent bet: " << account.bet << " kr.\n";
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
				<< "4) Show Stats\n"
				<< "5) Leave casino\n"
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
}