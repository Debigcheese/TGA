#include "Games.h"
#include "TableFunctions.h"
#include "Helpers.h"
#include "Print.h"

#include <iostream>

namespace Games
{
	using namespace Helpers;
	using namespace TableFunctions;
	using namespace Print;

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

	// ---------- Play Higher Or Lower ----------
	void PlayHigherOrLower(Account& account, Table& table)
	{
		Cards cards = {};
		HighOrLowPoints points = {};

		points.currentPoints = 0;
		int currentCardIndex = DrawRandomCard(cards);
		bool gameOver = false;

		while (!gameOver)
		{

			Print::ShowPersonalDetails(account);
			std::cout << "\n";

			std::cout << "Points: " << points.currentPoints << "\n";
			std::cout << "Current card: [" << cards.cardLabels[currentCardIndex] << "] \n\n";

			std::cout << "Is next card - \n";
			std::cout << "Higher: (1)\n";
			std::cout << "Lower:  (2)\n\n";
			std::cout << "Choice: ";

			int Higher = static_cast<int>(CardGuess::Higher);
			int Lower = static_cast<int>(CardGuess::Lower);

			int choice = ReadIntInRange(Higher, Lower);
			CardGuess cardGuess = static_cast<CardGuess>(choice);

			std::cout << "Drawing card... \n";
			system("pause");
			std::cout << "\n";

			int randomCardIndex = DrawRandomCard(cards);
			bool cardIsHigher = CompareCards(cards.cardValues[currentCardIndex], cards.cardValues[randomCardIndex]);

			std::cout << "You drew: [" << cards.cardLabels[randomCardIndex] << "]\n";
			std::cout << "You guessed [" << cards.cardLabels[randomCardIndex] << "]"
				<< " is ";
			if (cardGuess == CardGuess::Higher)
			{
				std::cout << "HIGHER than ";
			}
			else
			{
				std::cout << "LOWER than ";
			}
			std::cout << "[" << cards.cardLabels[currentCardIndex] << "] ";

			if ((cardGuess == CardGuess::Higher && cardIsHigher) || (cardGuess == CardGuess::Lower && !cardIsHigher))
			{
				std::cout << "which is CORRECT \n";
				points.currentPoints++;
			}
			else
			{
				std::cout << "which is FALSE \n";
			}

			if (IsHigherOrLowerGameOver(cards))
			{
				std::cout << "Deck of cards is empty!\n";
				std::cout << "You got: " << points.currentPoints << "/13 correct\n";
				std::cout << "Required points to win: " << points.requiredPoints << "/13 correct\n";

				if (points.currentPoints >= points.requiredPoints)
				{
					int win = account.bet * table.betMulti.betMultiHigherOrLower;
					account.money += win;
					table.moneyArr[TableToIndex(TableOption::HighOrLow)] += win;
					std::cout << "<--- 3X WIN! --->\n";
					std::cout << "Payout: " << win << " kr.\n""\n";
					UpdateStats(table, true);
				}
				else
				{
					account.money -= account.bet;
					table.moneyArr[TableToIndex(TableOption::HighOrLow)] -= account.bet;
					std::cout << "\nYou lost: " << account.bet << " kr.\n";
					UpdateStats(table, false);
				}
				gameOver = true;
			}

			system("pause");
			system("cls");
			currentCardIndex = randomCardIndex;
		}
	}

	void PlayRoulette(Account& account, Table& table)
	{
		Roulette roulette;

		while (true)
		{
			Print::ShowPersonalDetails(account);
			std::cout << "\n";
			DrawRouletteBoard(roulette);
			ShowRouletteBets();

			int choiceMin = static_cast<int>(RouletteBetType::Straight);
			int choiceMax = static_cast<int>(RouletteBetType::Column);

			int choice = ReadIntInRange(choiceMin, choiceMax);
			RouletteBetType betType = static_cast<RouletteBetType>(choice);

			system("cls");
			Print::ShowPersonalDetails(account);
			std::cout << "\n";
			DrawRouletteBoard(roulette);

			switch (betType)
			{
			case RouletteBetType::Straight:
			{
				std::cout << "\nPick your number!\n";
				std::cout << "Choice: ";
				int choiceStraight = ReadIntInRange(0, roulette.rouletteSize);
				roulette.betType.straight = choiceStraight;

				std::cout << "\nYou betted on: " << choiceStraight << "\n";
				break;
			}
			case RouletteBetType::RedBlack:
			{
				std::cout << "\nChoose Red or Black! \n";
				std::cout << "Red   (1)\n";
				std::cout << "Black (2)\n";
				std::cout << "Choice: ";

				int colorIndexMin = static_cast<int>(RouletteColor::Red);
				int colorIndexMax = static_cast<int>(RouletteColor::Black);

				int choiceColor = ReadIntInRange(colorIndexMin, colorIndexMax);

				roulette.betType.color = static_cast<RouletteColor>(choiceColor);

				std::string colorString = "";
				if (choiceColor == static_cast<int>(RouletteColor::Red))
				{
					colorString = "Red";
				}
				else
				{
					colorString = "Black";
				}

				std::cout << "\nYou betted on color: " << colorString << "\n";
				break;
			}
			case RouletteBetType::OddEven:
			{
				std::cout << "\nChoose odd or even! \n";
				std::cout << "Odd  (1)\n";
				std::cout << "Even (2)\n";
				std::cout << "Choice: ";

				int OddOrEvenMin = static_cast<int>(OddOrEven::Odd);
				int OddOrEvenMax = static_cast<int>(OddOrEven::Even);

				int choiceOddOrEven = ReadIntInRange(OddOrEvenMin, OddOrEvenMax);

				roulette.betType.OddOrEven = static_cast<OddOrEven>(choiceOddOrEven);

				std::string OddOrEvenString = "";
				if (choiceOddOrEven == static_cast<int>(OddOrEven::Odd))
				{
					OddOrEvenString = "Odd";
				}
				else
				{
					OddOrEvenString = "Even";
				}

				std::cout << "\nYou betted on: " << OddOrEvenString << "\n";
				break;
			}
			case RouletteBetType::Column:
			{
				std::cout << "\nChoose column! \n";
				std::cout << "Left Column   (1)\n";
				std::cout << "Middle Column (2)\n";
				std::cout << "Right Column  (3)\n";
				std::cout << "Choice: ";

				int colMin = static_cast<int>(Columns::Left);
				int colMax = static_cast<int>(Columns::Right);

				int choiceColumn = ReadIntInRange(colMin, colMax);

				roulette.betType.column = static_cast<Columns>(choiceColumn);

				std::string columnString = "";
				if (choiceColumn == static_cast<int>(Columns::Left))
				{
					columnString = "Left";
				}
				else if (choiceColumn == static_cast<int>(Columns::Middle))
				{
					columnString = "Middle";
				}
				else
				{
					columnString = "Right";
				}

				std::cout << "\nYou betted on: " << columnString << "\n";
				break;
			}
			default:
			{
				break;
			}
			}

			system("pause");
			std::cout << "\nBall is rolling... \n\n";
			system("pause");

			int winningNumber = GenerateRouletteNumber(roulette);

			std::cout << "\n" << "Your guess: ";








		}


	}
}