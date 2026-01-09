#include "TableFunctions.h"
#include "Print.h"
#include "Helpers.h"
#include "Games.h"
#include "Menu.h"

#include <random>
#include <iostream>

namespace TableFunctions
{
	using namespace Helpers;
	using namespace Print;
	using namespace Games;
	using namespace Menu;
	using namespace CONSTANTS;



	void ChangeBet(Account& account)
	{
		std::cout << "Enter bet (1 - " << account.money << "): ";
		int newBet = ReadIntInRange(1, account.money);

		account.bet = newBet;
		if (account.bet == account.money)
		{
			std::cout << "\nAll in! The guards raise an eyebrow as you push everything in...\n";
			system("pause");
		}
	}

	void HandleBankruptcy(Account& account, Table& table)
	{
		if (account.money <= 0)
		{
			std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
			std::cout << "\nYou leave with: " << account.money << "kr.";
			table.currentTable = TableOption::Quit;
		}
		if (account.money < account.bet && table.currentTable != TableOption::Quit)
		{
			std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
			ChangeBet(account);
		}

	}

	// Table
	bool EvaluateTableEarnings(Table& table)
	{
		int tableIndex = TableToIndex(table.currentTable);
		bool wonTooMuch = false;

		if (table.currentTable == TableOption::Quit)
		{
			return wonTooMuch;
		}

		if (table.moneyArr[tableIndex] == 0) // first time
		{
			std::cout << "\nThe dealer greets you with a sly smile.\n";

		}
		else if (table.moneyArr[tableIndex] > EARNINGS_MAX)
		{
			std::cout
				<< "\nYou've been on fire at this table, winning far too much...\n"
				<< "The pit boss whispers to the guards, and they politely escort you away.\n"
				<< "You are no longer welcome at this table.\n";
			wonTooMuch = true;
		}
		else if (table.moneyArr[tableIndex] < LOSSES_MAX)
		{
			std::cout
				<< "\nThis table has not been kind to you...\n"
				<< "The dealer smirks as your losses keep piling up.\n"
				<< "Maybe it's time to try your luck somewhere else.\n";
		}
		else
		{
			std::cout
				<< "\nYour streak here has been mixed, some wins, some losses.\n"
				<< "The dealer greets you with a sly smile.\n";
		}
		system("pause");
		return wonTooMuch;
	}

	void UpdateStats(Table& table, bool isWin)
	{

		int arrIndex = 0;
		const int statArrSize = sizeof(table.statArr) / sizeof(int);

		int statArrTemp[statArrSize] = {};

		for (int i = 0; i < statArrSize; i++)
		{
			statArrTemp[i] = table.statArr[i]; //make a copy array
		}

		for (int i = 0; i < statArrSize - 1; i++)
		{
			if (table.statArr[0] == ResultToIndex(Result::Empty))
			{
				break; //free spot
			}
			else
			{
				table.statArr[i + 1] = statArrTemp[i]; // move all indexes to the left [W][L][L][L][W] -> [0][W][L][L][L]
			}
		}

		arrIndex = 0;

		if (isWin)
		{
			table.statArr[arrIndex] = ResultToIndex(Result::Win);
		}
		else
		{
			table.statArr[arrIndex] = ResultToIndex(Result::Loss);
		}

		ShowStats(table);
	}

	bool IsHigherOrLowerGameOver(const Cards& cards)
	{
		int countCardsLeft = 0;
		for (int card : cards.cardsLeft)
		{
			if (card == 0)
			{
				countCardsLeft++;
			}
			if (countCardsLeft >= DECK_SIZE)
			{
				return true;
			}
		}
		return false;
	}



	//Higher or lower
	int DrawRandomCard(Cards& cards)
	{
		std::random_device rd;
		std::mt19937 rng{ rd() };
		std::uniform_int_distribution<int> dist(0, DECK_SIZE - 1);
		int randomCardIndex = 0;
		while (true)
		{
			randomCardIndex = dist(rng);

			if (cards.cardsLeft[randomCardIndex] != 0)
			{
				cards.cardsLeft[randomCardIndex] = 0;
				break;
			}
			if (IsHigherOrLowerGameOver(cards))
			{
				break;
			}
		}

		return randomCardIndex;
	}

	bool CompareCards(int previousCard, int newCard)
	{
		if (newCard > previousCard)
		{
			return true; //is higher
		}
		else
		{
			return false; //is lower
		}

	}



}