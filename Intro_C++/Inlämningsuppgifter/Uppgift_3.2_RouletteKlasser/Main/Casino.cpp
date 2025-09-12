#include "Casino.h"
#include "Print.h"
#include "Helpers.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

Casino::Casino()
{
}

void Casino::InitCasino()
{
	myGuessingGame.SetMoneyEarned(0);
	myOddOrEven.SetMoneyEarned(0);
	mySpinTheWheel.SetMoneyEarned(0);
	myHigherOrLower.SetMoneyEarned(0);
	myRoulette.SetMoneyEarned(0);
}

void Casino::RunCasino()
{
	//Casino(myGuessingGame, myOddOrEven, mySpinTheWheel, myHigherOrLower, myRoulette);
	InitCasino();
	ShowIntro(account);
	MainMenu();
}

//menus
void Casino::MainMenu()
{
	table.currentTable = TableOption::Menu;

	while (table.currentTable == TableOption::Menu && table.currentTable != TableOption::Quit)
	{
		ShowPersonalDetails(account);
		ShowOptions(table);
		HandleBankruptcy();

		TableOption chosenTable = static_cast<TableOption>(ReadIntInRange(//reads 1-5
			static_cast<int>(TableOption::GuessingGame),
			static_cast<int>(TableOption::Quit)));

		switch (chosenTable)
		{
		case TableOption::GuessingGame:
		{
			table.currentTable = TableOption::GuessingGame;
			break;
		}
		case TableOption::OddOrEven:
		{
			table.currentTable = TableOption::OddOrEven;
			break;
		}
		case TableOption::SpinTheWheel:
		{
			table.currentTable = TableOption::SpinTheWheel;
			break;
		}
		case TableOption::HighOrLow:
		{
			table.currentTable = TableOption::HighOrLow;
			break;
		}
		case TableOption::Roulette:
		{
			table.currentTable = TableOption::Roulette;
			break;
		}
		case TableOption::Stats:
		{
			ShowStats(table);
			system("pause");
			break;
		}
		case TableOption::Quit:
		{
			std::cout << "\nYou leave with " << account.money << " kr. Come back soon!\n";
			table.currentTable = TableOption::Quit;
			break;
		}
		default:
		{
			break;
		}
		}
		if (table.currentTable != TableOption::Quit && table.currentTable != TableOption::Menu)
		{
			if (!EvaluateTableEarnings())
			{
				EnterTable();
			}
			else
			{
				table.currentTable = TableOption::Menu;
			}
		}
	}
}
void Casino::EnterTable()
{
	TableOption chosenTable = table.currentTable;
	while (table.currentTable == chosenTable && table.currentTable != TableOption::Quit)
	{
		ShowPersonalDetails(account);
		ShowOptions(table);
		HandleBankruptcy();

		GameAction action = static_cast<GameAction>(ReadIntInRange( //reads 1-4
			static_cast<int>(GameAction::Play),
			static_cast<int>(GameAction::LeaveTable)));

		switch (action)
		{
		case GameAction::Play:
		{
			switch (table.currentTable)
			{
			case TableOption::GuessingGame:
			{
				myGuessingGame.PlayGuessingRound(account, table);
				break;
			}
			case TableOption::OddOrEven:
			{
				myOddOrEven.PlayOddEvenRound(account, table);
				break;
			}
			case TableOption::SpinTheWheel:
			{
				mySpinTheWheel.PlaySpinWheelRound(account, table);
				break;
			}
			case TableOption::HighOrLow:
			{
				myHigherOrLower.PlayHigherOrLower(account, table);
				break;
			}
			case TableOption::Roulette:
			{
				myRoulette.PlayRoulette(account, table);
				break;
			}
			default: break;
			}
			HandleBankruptcy();
			break;
		}
		case GameAction::ChangeBet:
		{
			ChangeBet();
			break;
		}
		case GameAction::ShowRules:
		{
			ShowRules(table);
			break;
		}
		case GameAction::LeaveTable:
		{
			table.currentTable = TableOption::Menu;
			break;
		}
		default:
		{
			break;
		}
		}
	}
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
void Casino::HandleBankruptcy()
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
		ChangeBet();
	}

}
void Casino::Payout(Account& account, Table& table, int payoutAmount)
{
	int win = account.bet;
	std::string payoutAmountString = myToString(payoutAmount);

	win *= payoutAmount;
	account.money += win;
	table.moneyArr[TableToIndex(table.currentTable)] += win;
	std::cout << "<--- " << payoutAmountString << "X WIN!--->\n";
	std::cout << "Your payout: " << win << " kr.\n";
	Casino::UpdateStats(table, true);

}
void Casino::UpdateStats(Table& table, bool isWin)
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
bool Casino::EvaluateTableEarnings()
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

