#include "Games.h"
#include "TableFunctions.h"
#include "Helpers.h"

#include <iostream>

namespace Games
{
	using namespace Helpers;
	using TableFunctions::UpdateStats;

	// ---------- Guessing Game ----------
	void PlayGuessingRound(Account& account, Table& table)
	{
		std::cout << "\nEnter your guess (2-12): ";
		int guess = ReadIntInRange(2, 12);

		int diceOne = RollDice();
		int diceTwo = RollDice();
		int sum = diceOne + diceTwo;

		std::cout << "\nDice 1: " << diceOne << ", Dice 2: " << diceTwo << "  -> Sum: " << sum << "\n";

		if (guess == sum)
		{
			int win = account.bet * table.betMulti.betMultiGuess;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::GuessingGame)] += win;
			std::cout << "BINGO! Your payout: " << win << " kr.\n";
			UpdateStats(table, true);
		}
		else
		{
			account.money -= account.bet;
			table.moneyArr[TableToIndex(TableOption::GuessingGame)] -= account.bet;
			std::cout << "Miss! You lose " << account.bet << " kr.\n";
			UpdateStats(table, false);
		}
		system("pause");
	}

	// ---------- Odd or Even ----------
	void PlayOddEvenRound(Account& account, Table& table)
	{
		std::cout << "\nChoose: Odd (1) or Even (2): ";
		int pick = ReadIntInRange(1, 2);

		int dice1 = RollDice();
		int dice2 = RollDice();
		std::cout << "Dice 1: " << dice1 << ", Dice 2: " << dice2 << "\n";

		bool dice1Odd = (dice1 % 2 == 1);
		bool dice2Odd = (dice2 % 2 == 1);

		bool bothOdd = dice1Odd && dice2Odd;
		bool bothEven = !dice1Odd && !dice2Odd;

		bool pickedOdd = (pick == 1);
		bool playerWins = (pickedOdd && bothOdd) || (!pickedOdd && bothEven);

		if (playerWins)
		{
			int win = account.bet * table.betMulti.betMultiOddOrEven;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::OddOrEven)] += win;
			std::cout << "You win! Your payout: " << win << " kr.\n";
			UpdateStats(table, true);
		}
		else
		{
			account.money -= account.bet;
			table.moneyArr[TableToIndex(TableOption::OddOrEven)] -= account.bet;
			std::cout << "House wins. You lose " << account.bet << " kr.\n";
			UpdateStats(table, false);
		}
		system("pause");
	}

	// ---------- Spin the wheel ----------
	void PlaySpinWheelRound(Account& account, Table& table)
	{
		std::cout << "\nSpin The Wheel (1):  ";
		ReadIntInRange(1, 1);

		int dice1 = RollDice();
		int dice2 = RollDice();
		int dice3 = RollDice();

		std::cout << dice1 << " | " << dice2 << " | " << dice3 << "\n";

		int win = account.bet;

		if (dice1 == dice2 && dice2 == dice3)
		{

			win *= table.betMulti.betMultiSpinWheelBig;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::SpinTheWheel)] += win;
			std::cout << "<--- 40X WIN! --->\n";
			std::cout << "Your payout: " << win << " kr.\n";
			UpdateStats(table, true);

		}
		else if ((dice1 == dice2) || (dice2 == dice3) || (dice3 == dice1))
		{

			win *= table.betMulti.betMultiSpinWheelSmall;
			account.money += win;
			table.moneyArr[TableToIndex(TableOption::SpinTheWheel)] += win;
			std::cout << "<--- 2X WIN! --->\n";
			std::cout << "Your payout: " << win << " kr.\n";
			UpdateStats(table, true);
		}
		else
		{
			account.money -= account.bet;
			table.moneyArr[TableToIndex(TableOption::SpinTheWheel)] -= account.bet;
			std::cout << "House wins. You lose " << account.bet << " kr.\n";
			UpdateStats(table, false);
		}
		system("pause");
	}
}