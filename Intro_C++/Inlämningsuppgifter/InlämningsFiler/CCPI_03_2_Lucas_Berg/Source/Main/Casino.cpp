#include "Casino.h"
#include "Print.h"
#include "Helpers.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

int Casino::ourStatArr[CONSTANTS::STAT_ARRAY_SIZE] = {};
char Casino::ourName[CONSTANTS::NAME_ARRAY_SIZE] = {};

Casino::Casino()
	: myGuessingGameLow
	{ CONSTANTS::GUESSING_GAME_STAKE_LOW_MIN,
	CONSTANTS::GUESSING_GAME_STAKE_LOW_MAX },
	myGuessingGameHigh
	{ GUESSING_GAME_STAKE_HIGH_MIN,
	GUESSING_GAME_STAKE_HIGH_MAX }
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
		ourStatArr[i] = 0;
	}
}

void Casino::RunCasino()
{
	InitCasino();
	ShowIntro(myAccount);
	ReadPlayerName();

	MainMenu();
}

void Casino::ReadPlayerName()
{
	while (true)
	{
		std::cout << "\nEnter your name (2-16 letters): ";
		std::cin.get(ourName, NAME_ARRAY_SIZE);

		if (std::cin.fail()) {
			std::cin.clear();                // clear failbit
			std::cin.ignore(10000, '\n');    // discard leftover characters
		}

		int length = static_cast<int>(strlen(ourName));
		bool valid = (length >= NAME_SIZE_MIN && length <= NAME_SIZE_MAX); // 2-16 characters

		for (int i = 0; i < length && valid; i++)
		{
			if (!isalpha(static_cast<unsigned char>(ourName[i])))
			{
				valid = false;
			}
		}
		if (valid)
		{
			break;
		}
		std::cout << "Invalid name. Use only letters, 2-16 characters.\n";
	}
}

const char* Casino::GetPlayerName()
{
	return ourName;
}

//menus 
void Casino::MainMenu()
{
	myCurrentTable = TableOption::TableOption_Menu;

	while (myCurrentTable == TableOption::TableOption_Menu && myCurrentTable != TableOption::TableOption_Quit)
	{
		ShowPersonalDetails(myAccount, ourStatArr, ourName);
		ShowOptions(myCurrentTable);
		HandleBankruptcy();

		TableOption chosenTable = static_cast<TableOption>(ReadIntInRange(//reads 1-5
			static_cast<int>(TableOption::TableOption_GuessingGame),
			static_cast<int>(TableOption::TableOption_Quit)));

		int moneyEarnedAtTable = 0;
		switch (chosenTable)
		{
		case TableOption::TableOption_GuessingGame:
		{
			myCurrentTable = TableOption::TableOption_Stakes;
			ChooseTableStakes();
			break;
		}
		case TableOption::TableOption_OddOrEven:
		{
			myCurrentTable = TableOption::TableOption_OddOrEven;
			moneyEarnedAtTable = myOddOrEven.GetMoneyEarned();
			break;
		}
		case TableOption::TableOption_SpinTheWheel:
		{
			myCurrentTable = TableOption::TableOption_SpinTheWheel;
			moneyEarnedAtTable = mySpinTheWheel.GetMoneyEarned();
			break;
		}
		case TableOption::TableOption_HighOrLow:
		{
			myCurrentTable = TableOption::TableOption_HighOrLow;
			moneyEarnedAtTable = myHigherOrLower.GetMoneyEarned();
			break;
		}
		case TableOption::TableOption_Roulette:
		{
			myCurrentTable = TableOption::TableOption_Roulette;
			moneyEarnedAtTable = myRoulette.GetMoneyEarned();
			break;
		}
		case TableOption::TableOption_Stats:
		{
			ShowStats(ourStatArr);
			std::cout << "\n";
			system("pause");
			break;
		}
		case TableOption::TableOption_Quit:
		{
			std::cout << "\nYou leave with " << myAccount.money << " kr. Come back soon ";
			ShowName(ourName);
			std::cout << "!\n";
			myStakes = Stakes::Stakes_None;
			myCurrentTable = TableOption::TableOption_Quit;
			break;
		}
		default:
		{
			break;
		}
		}
		if (myCurrentTable != TableOption::TableOption_Quit && myCurrentTable != TableOption::TableOption_Menu && myCurrentTable != TableOption::TableOption_Stakes)
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
	TableOption chosenTable = myCurrentTable;
	while (myCurrentTable == chosenTable && myCurrentTable != TableOption::TableOption_Quit && myCurrentTable != TableOption::TableOption_Stakes)
	{
		ShowPersonalDetails(myAccount, ourStatArr, ourName);
		ShowOptions(myCurrentTable);
		HandleBankruptcy();
		ValidateBet();

		GameAction action = static_cast<GameAction>(ReadIntInRange( //reads 1-4
			static_cast<int>(GameAction::GameAction_Play),
			static_cast<int>(GameAction::GameAction_LeaveTable)));

		switch (action)
		{
		case GameAction::GameAction_Play:
		{
			switch (myCurrentTable)
			{
			case TableOption::TableOption_GuessingGame:
			{
				if (myStakes == Stakes::Stakes_Low)
				{
					myGuessingGameLow.PlayGuessingRound(myAccount);
					break;
				}
				else if (myStakes == Stakes::Stakes_High)
				{
					myGuessingGameHigh.PlayGuessingRound(myAccount);
					break;
				}
				else
				{
					break;
				}
			}
			case TableOption::TableOption_OddOrEven:
			{
				myOddOrEven.PlayOddEvenRound(myAccount);
				break;
			}
			case TableOption::TableOption_SpinTheWheel:
			{
				mySpinTheWheel.PlaySpinWheelRound(myAccount);
				break;
			}
			case TableOption::TableOption_HighOrLow:
			{
				myHigherOrLower.PlayHigherOrLower(myAccount);
				break;
			}
			case TableOption::TableOption_Roulette:
			{
				myRoulette.PlayRoulette(myAccount);
				break;
			}
			default: break;
			}
			HandleBankruptcy();
			break;
		}
		case GameAction::GameAction_ChangeBet:
		{
			if (myStakes == Stakes::Stakes_None)
			{
				ChangeBet();
			}
			else if (myStakes == Stakes::Stakes_Low)
			{
				ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
			}
			else if (myStakes == Stakes::Stakes_High)
			{
				if (myAccount.money < myGuessingGameHigh.GetBetMinimum())
				{
					std::cout << "\nYou dont have enough credit to play on this table\n";
					system("pause");
					break;
				}
				ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
			}
			break;
		}
		case GameAction::GameAction_ShowRules:
		{
			ShowRules(myCurrentTable);
			break;
		}
		case GameAction::GameAction_LeaveTable:
		{
			myCurrentTable = TableOption::TableOption_Menu;
			myStakes = Stakes::Stakes_None;
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
	while (myCurrentTable == TableOption::TableOption_Stakes && myCurrentTable != TableOption::TableOption_Quit)
	{

		ShowPersonalDetails(myAccount, ourStatArr, ourName);
		HandleBankruptcy();

		std::cout
			<< "\n=== Stakes: Guess The Sum ===\n"
			<< "1) Low stakes (" << myGuessingGameLow.GetBetMinimum() << " - " << myGuessingGameLow.GetBetMaximum() << ")\n"
			<< "2) High stakes (" << myGuessingGameHigh.GetBetMinimum() << " - " << myGuessingGameHigh.GetBetMaximum() << ")\n"
			<< "3) Return\n"
			<< "Choice: ";

		myStakes = static_cast<Stakes>(ReadIntInRange( //reads 1-3
			static_cast<int>(Stakes::Stakes_Low),
			static_cast<int>(Stakes::Stakes_None)));

		switch (myStakes)
		{
		case Stakes::Stakes_Low:
		{
			if (EvaluateTableEarnings(myGuessingGameLow.GetMoneyEarned()))
			{
				break;
			}
			myCurrentTable = TableOption::TableOption_GuessingGame;
			ValidateBet();
			EnterTable();
			break;
		}
		case Stakes::Stakes_High:
		{
			if (myAccount.money < myGuessingGameHigh.GetBetMinimum())
			{
				std::cout << "\nYou dont have enough credit to enter this table\n";
				system("pause");
				break;
			}
			if (EvaluateTableEarnings(myGuessingGameHigh.GetMoneyEarned()))
			{
				break;
			}
			myCurrentTable = TableOption::TableOption_GuessingGame;
			ValidateBet();
			EnterTable();
			break;

		}
		case Stakes::Stakes_None: //return
		{
			myStakes = Stakes::Stakes_None;
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
	return ourStatArr;
}

//casino table & menu functions
void Casino::ChangeBet()
{
	std::cout << "Enter bet (1 - " << myAccount.money << "): ";
	int newBet = ReadIntInRange(1, myAccount.money);

	myAccount.bet = newBet;
	if (myAccount.bet == myAccount.money)
	{
		std::cout << "\nAll in! The guards raise an eyebrow as you push everything in...\n";
		system("pause");
	}
}
void Casino::ChangeBetInRange(const int aBetMin, int aBetMax)
{
	if (myAccount.money < aBetMax)
	{
		aBetMax = myAccount.money;
	}
	std::cout << "Enter bet (" << aBetMin << " - " << aBetMax << "): ";
	int newBet = ReadIntInRange(aBetMin, aBetMax);

	myAccount.bet = newBet;
	if (myAccount.bet == myAccount.money)
	{
		std::cout << "\nAll in! The guards raise an eyebrow as you push everything in...\n";
		system("pause");
	}
}
void Casino::ValidateBet()
{
	if (myStakes == Stakes::Stakes_Low)
	{
		if (myAccount.bet > myGuessingGameLow.GetBetMaximum())
		{
			std::cout << "\nYour bet is higher than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
		}
		else if (myAccount.bet < myGuessingGameLow.GetBetMinimum())
		{
			std::cout << "\nYour bet is lower than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
		}
	}
	else if (myStakes == Stakes::Stakes_High)
	{
		if (myAccount.money < myGuessingGameHigh.GetBetMinimum())
		{
			std::cout << "\nYou dont have enough credit for this table anymore\n";
			myStakes = Stakes::Stakes_None;
			system("pause");
			MainMenu();
		}
		else if (myAccount.bet > myGuessingGameHigh.GetBetMaximum())
		{
			std::cout << "\nYour bet is higher than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
		}
		else if (myAccount.bet < myGuessingGameHigh.GetBetMinimum())
		{
			std::cout << "\nYour bet is lower than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
		}
	}
}
void Casino::HandleBankruptcy()
{
	if (myAccount.money <= 0)
	{
		std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
		std::cout << "\nYou leave with: " << myAccount.money << "kr.";
		myCurrentTable = TableOption::TableOption_Quit;
	}
	if (myAccount.money < myAccount.bet && myCurrentTable != TableOption::TableOption_Quit)
	{
		std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
		ChangeBet();
	}
}

int Casino::Payout(Account& aAccount, const int aPayoutAmount)
{
	int win = aAccount.bet;
	std::string payoutAmountString = myToString(aPayoutAmount);

	win *= aPayoutAmount;
	aAccount.money += win;
	std::cout << "\n<--- " << payoutAmountString << "X WIN!--->\n";
	std::cout << "You won this time ";
	ShowName(ourName);
	std::cout << ", dont get your hopes up.\n";
	std::cout << "Your payout: " << win << " kr.\n";

	return win;
}

int Casino::DeductBet(Account& aAccount)
{
	aAccount.money -= aAccount.bet;
	std::cout << "\nUnlucky for you mister ";
	ShowName(ourName);
	std::cout << "\nHouse wins, you lose: " << aAccount.bet << " kr.\n";

	return aAccount.bet;
}

void Casino::UpdateStats(bool aIsWin)
{
	int arrIndex = 0;
	const int statArrSize = sizeof(ourStatArr) / sizeof(int);

	int statArrTemp[statArrSize] = {};

	for (int i = 0; i < statArrSize; i++)
	{
		statArrTemp[i] = ourStatArr[i]; //make a copy array
	}

	for (int i = 0; i < statArrSize - 1; i++)
	{
		if (ourStatArr[0] == ResultToIndex(Result::Result_Empty))
		{
			break; //free spot
		}
		else
		{
			ourStatArr[i + 1] = statArrTemp[i]; // move all indexes to the left [W][L][L][L][W] -> [0][W][L][L][L]
		}
	}

	arrIndex = 0;

	if (aIsWin)
	{
		ourStatArr[arrIndex] = ResultToIndex(Result::Result_Win);
	}
	else
	{
		ourStatArr[arrIndex] = ResultToIndex(Result::Result_Loss);
	}

	ShowStats(ourStatArr);
}
bool Casino::EvaluateTableEarnings(const int aMoneyEarnedAtTable) const
{
	bool wonTooMuch = false;
	bool shouldQuit = true;
	int earningsMax = EARNINGS_MAX;
	int LossesMax = LOSSES_MAX;

	if (myStakes == Stakes::Stakes_Low)
	{
		earningsMax = EARNINGS_MAX + myGuessingGameLow.GetBetMaximum();
		LossesMax = LOSSES_MAX - myGuessingGameLow.GetBetMaximum();
	}
	else if (myStakes == Stakes::Stakes_High)
	{
		earningsMax = EARNINGS_MAX + myGuessingGameHigh.GetBetMaximum();
		LossesMax = LOSSES_MAX - myGuessingGameHigh.GetBetMaximum();
	}

	if (myCurrentTable == TableOption::TableOption_Quit)
	{
		return shouldQuit;
	}

	if (aMoneyEarnedAtTable == 0) // first time
	{
		std::cout << "\nHello ";
		ShowName(ourName);
		std::cout << "!\n";
		std::cout << "Ready to lose some money? \033[3msmiles\033[0m\n";

	}
	else if (aMoneyEarnedAtTable > earningsMax)
	{
		wonTooMuch = true;
		std::cout
			<< "\nYou've been on fire at this table ";
		ShowName(ourName);
		std::cout
			<< ", winning far too much...\n"
			<< "The pit boss whispers to the guards, and they politely escort you away.\n"
			<< "You are no longer welcome at this table.\n";

	}
	else if (aMoneyEarnedAtTable < LossesMax)
	{
		std::cout
			<< "\nThis table has not been kind to you ";
		ShowName(ourName);
		std::cout
			<< "...\n"
			<< "The dealer smirks as your losses keep piling up.\n"
			<< "Maybe it's time to try your luck somewhere else.\n";
	}
	else
	{
		std::cout
			<< "\nYour streak here has been mixed ";
		ShowName(ourName);
		std::cout
			<< ", some wins, some losses.\n"
			<< "\033[3mThe dealer greets you with a sly smile.\033[0m\n";
	}
	system("pause");
	return wonTooMuch;
}

