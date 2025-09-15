#include "Casino.h"
#include "Print.h"
#include "Helpers.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

int Casino::statArr[CONSTANTS::STAT_ARRAY_SIZE] = {};

Casino::Casino()
	: myGuessingGameLow{ 1, 1000 }, myGuessingGameHigh{ 1000, 100000 }
{
}

void Casino::InitCasino()
{
	myGuessingGameLow.SetMoneyEarned(0);
	myGuessingGameHigh.SetMoneyEarned(0);
	myOddOrEven.SetMoneyEarned(0);
	mySpinTheWheel.SetMoneyEarned(0);
	myHigherOrLower.SetMoneyEarned(0);
	myRoulette.SetMoneyEarned(0);

	for (int i = 0; i < CONSTANTS::STAT_ARRAY_SIZE; ++i)
	{
		statArr[i] = 0;
	}
}

void Casino::RunCasino()
{
	InitCasino();
	ShowIntro(account);
	MainMenu();
}

//menus
void Casino::MainMenu()
{
	currentTable = TableOption::Menu;

	while (currentTable == TableOption::Menu && currentTable != TableOption::Quit)
	{
		ShowPersonalDetails(account, statArr);
		ShowOptions(currentTable);
		HandleBankruptcy();

		TableOption chosenTable = static_cast<TableOption>(ReadIntInRange(//reads 1-5
			static_cast<int>(TableOption::GuessingGame),
			static_cast<int>(TableOption::Quit)));

		int moneyEarnedAtTable = 0;
		switch (chosenTable)
		{
		case TableOption::GuessingGame:
		{
			currentTable = TableOption::Stakes;
			ChooseTableStakes();
			break;
		}
		case TableOption::OddOrEven:
		{
			currentTable = TableOption::OddOrEven;
			moneyEarnedAtTable = myOddOrEven.GetMoneyEarned();
			break;
		}
		case TableOption::SpinTheWheel:
		{
			currentTable = TableOption::SpinTheWheel;
			moneyEarnedAtTable = mySpinTheWheel.GetMoneyEarned();
			break;
		}
		case TableOption::HighOrLow:
		{
			currentTable = TableOption::HighOrLow;
			moneyEarnedAtTable = myHigherOrLower.GetMoneyEarned();
			break;
		}
		case TableOption::Roulette:
		{
			currentTable = TableOption::Roulette;
			moneyEarnedAtTable = myRoulette.GetMoneyEarned();
			break;
		}
		case TableOption::Stats:
		{
			ShowStats(statArr);
			system("pause");
			break;
		}
		case TableOption::Quit:
		{
			std::cout << "\nYou leave with " << account.money << " kr. Come back soon!\n";
			stakes = Stakes::None;
			currentTable = TableOption::Quit;
			break;
		}
		default:
		{
			break;
		}
		}
		if (currentTable != TableOption::Quit && currentTable != TableOption::Menu && currentTable != TableOption::Stakes)
		{
			if (!EvaluateTableEarnings(moneyEarnedAtTable))
			{
				EnterTable();
			}
		}
	}
}
void Casino::EnterTable()
{
	TableOption chosenTable = currentTable;
	while (currentTable == chosenTable && currentTable != TableOption::Quit && currentTable != TableOption::Stakes)
	{
		ShowPersonalDetails(account, statArr);
		ShowOptions(currentTable);
		HandleBankruptcy();
		ValidateBet();

		GameAction action = static_cast<GameAction>(ReadIntInRange( //reads 1-4
			static_cast<int>(GameAction::Play),
			static_cast<int>(GameAction::LeaveTable)));

		switch (action)
		{
		case GameAction::Play:
		{
			switch (currentTable)
			{
			case TableOption::GuessingGame:
			{
				if (stakes == Stakes::Low)
				{
					myGuessingGameLow.PlayGuessingRound(account);
					break;
				}
				else if (stakes == Stakes::High)
				{
					myGuessingGameHigh.PlayGuessingRound(account);
					break;
				}
				else
				{
					break;
				}
			}
			case TableOption::OddOrEven:
			{
				myOddOrEven.PlayOddEvenRound(account);
				break;
			}
			case TableOption::SpinTheWheel:
			{
				mySpinTheWheel.PlaySpinWheelRound(account);
				break;
			}
			case TableOption::HighOrLow:
			{
				myHigherOrLower.PlayHigherOrLower(account);
				break;
			}
			case TableOption::Roulette:
			{
				myRoulette.PlayRoulette(account);
				break;
			}
			default: break;
			}
			HandleBankruptcy();
			break;
		}
		case GameAction::ChangeBet:
		{
			if (stakes == Stakes::None)
			{
				ChangeBet();
			}
			else if (stakes == Stakes::Low)
			{
				ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
			}
			else if (stakes == Stakes::High)
			{
				if (account.money < myGuessingGameHigh.GetBetMinimum())
				{
					std::cout << "\nYou dont have enough credit to play on this table\n";
					system("pause");
					break;
				}
				ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
			}
			break;
		}
		case GameAction::ShowRules:
		{
			ShowRules(currentTable);
			break;
		}
		case GameAction::LeaveTable:
		{
			currentTable = TableOption::Menu;
			stakes = Stakes::None;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void Casino::ChooseTableStakes()
{
	while (currentTable == TableOption::Stakes && currentTable != TableOption::Quit)
	{

		ShowPersonalDetails(account, statArr);
		HandleBankruptcy();

		std::cout
			<< "\n=== Stakes: Guess The Sum ===\n"
			<< "1) Low stakes (" << myGuessingGameLow.GetBetMinimum() << " - " << myGuessingGameLow.GetBetMaximum() << ")\n"
			<< "2) High stakes (" << myGuessingGameHigh.GetBetMinimum() << " - " << myGuessingGameHigh.GetBetMaximum() << ")\n"
			<< "3) Return\n"
			<< "Choice: ";

		stakes = static_cast<Stakes>(ReadIntInRange( //reads 1-2
			static_cast<int>(Stakes::Low),
			static_cast<int>(Stakes::None)));

		switch (stakes)
		{
		case Stakes::Low:
		{
			if (EvaluateTableEarnings(myGuessingGameLow.GetMoneyEarned()))
			{
				break;
			}
			currentTable = TableOption::GuessingGame;
			ValidateBet();
			EnterTable();
			break;
		}
		case Stakes::High:
		{
			if (account.money < myGuessingGameHigh.GetBetMinimum())
			{
				std::cout << "\nYou dont have enough credit to enter this table\n";
				system("pause");
				break;
			}
			if (EvaluateTableEarnings(myGuessingGameHigh.GetMoneyEarned()))
			{
				break;
			}
			currentTable = TableOption::GuessingGame;
			ValidateBet();
			EnterTable();
			break;

		}
		case Stakes::None:
		{
			stakes = Stakes::None;
			MainMenu();
			break;
		}
		default:
		{
			break;
		}
		}
	}
}
const int* Casino::GetStatArr()
{
	return statArr;
}

//casino table & menu functions
void Casino::ChangeBet()
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
void Casino::ChangeBetInRange(int aBetMin, int aBetMax)
{
	if (account.money < aBetMax)
	{
		aBetMax = account.money;
	}
	std::cout << "Enter bet (" << aBetMin << " - " << aBetMax << "): ";
	int newBet = ReadIntInRange(aBetMin, aBetMax);

	account.bet = newBet;
	if (account.bet == account.money)
	{
		std::cout << "\nAll in! The guards raise an eyebrow as you push everything in...\n";
		system("pause");
	}
}
void Casino::ValidateBet()
{
	if (stakes == Stakes::Low)
	{
		if (account.bet > myGuessingGameLow.GetBetMaximum())
		{
			std::cout << "\nYour bet is higher than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
		}
		else if (account.bet < myGuessingGameLow.GetBetMinimum())
		{
			std::cout << "\nYour bet is lower than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
		}
	}
	else if (stakes == Stakes::High)
	{
		if (account.money < myGuessingGameHigh.GetBetMinimum())
		{
			std::cout << "\nYou dont have enough credit for this table anymore\n";
			stakes = Stakes::None;
			system("pause");
			MainMenu();
		}
		else if (account.bet > myGuessingGameHigh.GetBetMaximum())
		{
			std::cout << "\nYour bet is higher than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
		}
		else if (account.bet < myGuessingGameHigh.GetBetMinimum())
		{
			std::cout << "\nYour bet is lower than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
		}
	}
}
void Casino::HandleBankruptcy()
{
	if (account.money <= 0)
	{
		std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
		std::cout << "\nYou leave with: " << account.money << "kr.";
		currentTable = TableOption::Quit;
	}
	if (account.money < account.bet && currentTable != TableOption::Quit)
	{
		std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
		ChangeBet();
	}
}

int Casino::Payout(Account& account, int payoutAmount)
{
	int win = account.bet;
	std::string payoutAmountString = myToString(payoutAmount);

	win *= payoutAmount;
	account.money += win;
	std::cout << "<--- " << payoutAmountString << "X WIN!--->\n";
	std::cout << "Your payout: " << win << " kr.\n";

	return win;
}

int Casino::DeductBet(Account& account)
{
	account.money -= account.bet;
	std::cout << "House wins. You lose " << account.bet << " kr.\n";

	return account.bet;
}

void Casino::UpdateStats(bool isWin)
{
	int arrIndex = 0;
	const int statArrSize = sizeof(statArr) / sizeof(int);

	int statArrTemp[statArrSize] = {};

	for (int i = 0; i < statArrSize; i++)
	{
		statArrTemp[i] = statArr[i]; //make a copy array
	}

	for (int i = 0; i < statArrSize - 1; i++)
	{
		if (statArr[0] == ResultToIndex(Result::Empty))
		{
			break; //free spot
		}
		else
		{
			statArr[i + 1] = statArrTemp[i]; // move all indexes to the left [W][L][L][L][W] -> [0][W][L][L][L]
		}
	}

	arrIndex = 0;

	if (isWin)
	{
		statArr[arrIndex] = ResultToIndex(Result::Win);
	}
	else
	{
		statArr[arrIndex] = ResultToIndex(Result::Loss);
	}

	ShowStats(statArr);
}
bool Casino::EvaluateTableEarnings(const int moneyEarnedAtTable) const
{
	bool wonTooMuch = false;
	bool shouldQuit = true;
	int earningsMax = EARNINGS_MAX;
	int LossesMax = LOSSES_MAX;

	if (stakes == Stakes::Low)
	{
		earningsMax = EARNINGS_MAX + myGuessingGameLow.GetBetMaximum();
		LossesMax = LOSSES_MAX + myGuessingGameLow.GetBetMaximum();
	}
	else if (stakes == Stakes::High)
	{
		earningsMax = EARNINGS_MAX + myGuessingGameHigh.GetBetMaximum();
		LossesMax = LOSSES_MAX + myGuessingGameHigh.GetBetMaximum();
	}

	if (currentTable == TableOption::Quit)
	{
		return shouldQuit;
	}

	if (moneyEarnedAtTable == 0) // first time
	{
		std::cout << "\nThe dealer greets you with a sly smile.\n";

	}
	else if (moneyEarnedAtTable > earningsMax)
	{
		wonTooMuch = true;
		std::cout
			<< "\nYou've been on fire at this table, winning far too much...\n"
			<< "The pit boss whispers to the guards, and they politely escort you away.\n"
			<< "You are no longer welcome at this table.\n";

	}
	else if (moneyEarnedAtTable < LossesMax)
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

