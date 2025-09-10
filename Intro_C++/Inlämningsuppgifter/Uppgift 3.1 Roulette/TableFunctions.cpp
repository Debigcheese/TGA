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
	using namespace TableFunctions;
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

	void RoulettePayout(Account& account, Table& table, RouletteBetType rouletteBetType)
	{
		if (rouletteBetType == RouletteBetType::Straight)
		{
			int win = account.bet * BET_MULTI_ROULETTE_STRAIGHT;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::Roulette)] += win;
			std::cout << "<--- 36X WIN! --->\n";
			std::cout << "Payout: " << win << " kr.\n""\n";
			UpdateStats(table, true);
		}
		else if (rouletteBetType == RouletteBetType::RedBlack)
		{
			int win = account.bet * BET_MULTI_ROULETTE_COLOR;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::Roulette)] += win;
			std::cout << "<--- 2X WIN! --->\n";
			std::cout << "Payout: " << win << " kr.\n""\n";
			UpdateStats(table, true);
		}
		else if (rouletteBetType == RouletteBetType::OddEven)
		{
			int win = account.bet * BET_MULTI_ROULETTE_ODDOREVEN;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::Roulette)] += win;
			std::cout << "<--- 2X WIN! --->\n";
			std::cout << "Payout: " << win << " kr.\n""\n";
			UpdateStats(table, true);
		}
		else if (rouletteBetType == RouletteBetType::Column)
		{
			int win = account.bet * BET_MULTI_ROULETTE_COLUMN;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::Roulette)] += win;
			std::cout << "<--- 3X WIN! --->\n";
			std::cout << "Payout: " << win << " kr.\n""\n";
			UpdateStats(table, true);
		}
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

	void DrawRouletteBoard(const Roulette& roulette)
	{
		for (int i = 0; i < ROULETTE_ARRAY_SIZE; i++)
		{
			if (i == 0)
			{
				std::cout << "    [" << roulette.rouletteLayout[i] << "]\n";
			}
			else
			{
				if ((i != 1 && i != 4 && i != 7) && i < 10)
				{
					std::cout << " ";
				}
				RouletteColor indexColor = GetColorFromIndex(roulette.rouletteLayout, i);
				PrintBracketsWithColor(indexColor, 0);
				PrintIndexWithColor(indexColor, i);
				PrintBracketsWithColor(indexColor, 1);

				if (i % 3 == 0)
				{
					std::cout << "\n";
				}

			}
		}
	}

	int GenerateRouletteNumber(const Roulette& roulette)
	{
		std::random_device rd;
		std::mt19937 rng{ rd() };
		std::uniform_int_distribution<int> dist(0, ROULETTE_ARRAY_SIZE);

		int randomRouletteNumber = dist(rng);

		return randomRouletteNumber;
	}

	bool RouletteStraightGuess(Roulette& roulette, const int& winningNumber)
	{
		if (roulette.betType == RouletteBetType::Straight &&
			roulette.betPerType.straight == winningNumber)
		{
			return true;
		}
		return false;
	}

	RouletteColor RouletteColorGuess(Roulette& roulette, const int& winningNumber)
	{
		RouletteColor color = GetColorFromIndex(roulette.rouletteLayout, winningNumber);

		if (roulette.betPerType.color == color)
		{
			return color;
		}

		return RouletteColor::None;
	}

	OddOrEven RouletteOddOrEvenGuess(Roulette& roulette, const int& winningNumber)
	{
		OddOrEven OddOrEven = GetOddOrEvenFromIndex(winningNumber);

		if (roulette.betPerType.OddOrEven == OddOrEven && roulette.betPerType.OddOrEven == OddOrEven::Even)
		{
			return OddOrEven::Even;
		}
		else if (roulette.betPerType.OddOrEven == OddOrEven && roulette.betPerType.OddOrEven == OddOrEven::Odd)
		{
			return OddOrEven::Odd;
		}
		return OddOrEven::None;
	}

	Columns RouletteColumnGuess(Roulette& roulette, const int& winningNumber)
	{
		if (roulette.betPerType.column == Columns::Left && winningNumber % 3 == 0 && winningNumber != 0)
		{
			return Columns::Left;
		}
		else if (roulette.betPerType.column == Columns::Middle && winningNumber % 3 == 1 && winningNumber != 0)
		{
			return Columns::Middle;
		}
		else if (roulette.betPerType.column == Columns::Right && winningNumber % 3 == 2 && winningNumber != 0)
		{
			return Columns::Right;
		}

		return Columns::None;
	}



}