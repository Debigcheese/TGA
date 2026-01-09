#include "Casino.h"
#include "Print.h"
#include "Helpers.h"

#include <iostream>

using namespace Helpers;
using namespace Print;

int Casino::ourStatArr[STAT_ARRAY_SIZE] = {};
char Casino::ourName[NAME_ARRAY_SIZE] = {};

Casino::Casino()
	: myAccount({myDefaultMoney, myDefaultBet}),
	  myCurrentTable(myDefaultTable),
	  myStakes(myDefaultStakes),
	  myGuessingGameLow
	  {
		  GUESSING_GAME_STAKE_LOW_MIN,
		  GUESSING_GAME_STAKE_LOW_MAX
	  },
	  myGuessingGameHigh
	  {
		  GUESSING_GAME_STAKE_HIGH_MIN,
		  GUESSING_GAME_STAKE_HIGH_MAX
	  }
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


	for (auto& a : ourStatArr)
	{
		a = 0;
	}
}

void Casino::RunCasino()
{
	InitCasino();
	ShowIntro(myAccount);
	ReadPlayerName();

	EnterMainMenu();
}

void Casino::ReadPlayerName() const
{
	while (true)
	{
		std::cout << "\nEnter your name (2-16 letters): ";
		std::cin.get(ourName, NAME_ARRAY_SIZE);

		if (std::cin.fail())
		{
			std::cin.clear(); // clear failbit
			std::cin.ignore(CIN_IGNORE_MAX, '\n'); // discard leftover characters
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
void Casino::EnterMainMenu()
{
	myCurrentTable = TableOption::Menu;
	myStakes = Stakes::None;

	while (myCurrentTable == TableOption::Menu && myCurrentTable != TableOption::Quit)
	{
		ShowPersonalDetails(myAccount, ourStatArr, ourName);
		ShowOptions(myCurrentTable);
		if (HandleBankruptcy())
		{
			return;
		}
		auto chosenTable = static_cast<TableOption>(ReadIntInRange( //reads 1-5
			static_cast<int>(TableOption::GuessingGame),
			static_cast<int>(TableOption::Quit)));

		int moneyEarnedAtTable = 0;
		switch (chosenTable)
		{
			case TableOption::GuessingGame:
			{
				myCurrentTable = TableOption::Stakes;
				ChooseTableStakes();
				break;
			}
			case TableOption::OddOrEven:
			{
				myCurrentTable = TableOption::OddOrEven;
				moneyEarnedAtTable = myOddOrEven.GetMoneyEarned();
				break;
			}
			case TableOption::SpinTheWheel:
			{
				myCurrentTable = TableOption::SpinTheWheel;
				moneyEarnedAtTable = mySpinTheWheel.GetMoneyEarned();
				break;
			}
			case TableOption::HighOrLow:
			{
				myCurrentTable = TableOption::HighOrLow;
				moneyEarnedAtTable = myHigherOrLower.GetMoneyEarned();
				break;
			}
			case TableOption::Roulette:
			{
				myCurrentTable = TableOption::Roulette;
				moneyEarnedAtTable = myRoulette.GetMoneyEarned();
				break;
			}
			case TableOption::Stats:
			{
				ShowStats(ourStatArr);
				std::cout << "\n";
				system("pause");
				break;
			}
			case TableOption::Quit:
			{
				std::cout << "\nYou leave with " << myAccount.money << " kr. Come back soon ";
				ShowName(ourName);
				std::cout << "!\n";
				myStakes = Stakes::None;
				myCurrentTable = TableOption::Quit;
				return;
			}
			default:
			{
				break;
			}
		}
		if (myCurrentTable != TableOption::Quit && myCurrentTable != TableOption::Menu &&
			myCurrentTable != TableOption::Stakes)
		{
			if (!EvaluateTableEarnings(moneyEarnedAtTable))
			{
				EnterTable();
			}
		}
		if (myCurrentTable != TableOption::Quit)
		{
			myCurrentTable = TableOption::Menu;
		}
	}
}

void Casino::EnterTable()
{
	TableOption chosenTable = myCurrentTable;
	while (myCurrentTable == chosenTable && myCurrentTable != TableOption::Quit && myCurrentTable !=
		TableOption::Stakes)
	{
		ShowPersonalDetails(myAccount, ourStatArr, ourName);
		ShowOptions(myCurrentTable);
		if (HandleBankruptcy())
		{
			return;
		}
		if (ValidateBet())
		{
			continue;
		}

		auto action = static_cast<GameAction>(ReadIntInRange( //reads 1-4
			static_cast<int>(GameAction::Play),
			static_cast<int>(GameAction::LeaveTable)));

		switch (action)
		{
			case GameAction::Play:
			{
				switch (myCurrentTable)
				{
					case TableOption::GuessingGame:
					{
						if (myStakes == Stakes::Low)
						{
							myGuessingGameLow.PlayGuessingRound(myAccount);
							break;
						}
						if (myStakes == Stakes::High)
						{
							myGuessingGameHigh.PlayGuessingRound(myAccount);
							break;
						}
						break;
					}
					case TableOption::OddOrEven:
					{
						myOddOrEven.PlayOddEvenRound(myAccount);
						break;
					}
					case TableOption::SpinTheWheel:
					{
						mySpinTheWheel.PlaySpinWheelRound(myAccount);
						break;
					}
					case TableOption::HighOrLow:
					{
						myHigherOrLower.PlayHigherOrLower(myAccount);
						break;
					}
					case TableOption::Roulette:
					{
						myRoulette.PlayRoulette(myAccount);
						break;
					}
					default:
						break;
				}
				if (HandleBankruptcy())
				{
					return;
				}
				break;
			}
			case GameAction::ChangeBet:
			{
				if (myStakes == Stakes::Low && myCurrentTable == TableOption::GuessingGame)
				{
					ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
					break;
				}
				if (myStakes == Stakes::High && myCurrentTable == TableOption::GuessingGame)
				{
					if (myAccount.money < myGuessingGameHigh.GetBetMinimum())
					{
						std::cout << "\nYou dont have enough credit to play on this table\n";
						system("pause");
						break;
					}
					ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
					break;
				}
				if (myStakes == Stakes::None && myCurrentTable != TableOption::GuessingGame)
				{
					ChangeBet();
				}
				break;
			}
			case GameAction::ShowRules:
			{
				ShowRules(myCurrentTable);
				break;
			}
			case GameAction::LeaveTable:
			{
				myCurrentTable = TableOption::Menu;
				myStakes = Stakes::None;
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
	while (myCurrentTable == TableOption::Stakes && myCurrentTable != TableOption::Quit)
	{
		ShowPersonalDetails(myAccount, ourStatArr, ourName);
		if (HandleBankruptcy())
		{
			return;
		}

		std::cout
			<< "\n=== Stakes: Guess The Sum ===\n"
			<< "1) Low stakes (" << myGuessingGameLow.GetBetMinimum() << " - " << myGuessingGameLow.GetBetMaximum() <<
			")\n"
			<< "2) High stakes (" << myGuessingGameHigh.GetBetMinimum() << " - " << myGuessingGameHigh.GetBetMaximum()
			<< ")\n"
			<< "3) Return\n"
			<< "Choice: ";

		myStakes = static_cast<Stakes>(ReadIntInRange( //reads 1-3
			static_cast<int>(Stakes::Low),
			static_cast<int>(Stakes::None)));

		switch (myStakes)
		{
			case Stakes::Low:
			{
				if (EvaluateTableEarnings(myGuessingGameLow.GetMoneyEarned()))
				{
					break;
				}
				myCurrentTable = TableOption::GuessingGame;
				ValidateBet();
				EnterTable();
				break;
			}
			case Stakes::High:
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
				myCurrentTable = TableOption::GuessingGame;
				ValidateBet();
				EnterTable();
				break;
			}
			case Stakes::None: //return
			{
				myStakes = Stakes::None;
				EnterMainMenu();
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

int Casino::GetStatArrSize()
{
	return STAT_ARRAY_SIZE;
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
	if (aBetMin == aBetMax)
	{
		myAccount.bet = aBetMin;
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

bool Casino::ValidateBet()
{
	if (myStakes == Stakes::Low)
	{
		if (myAccount.money < myAccount.bet)
		{
			std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
			return true;
		}
		if (myAccount.bet > myGuessingGameLow.GetBetMaximum())
		{
			std::cout << "\nYour bet is higher than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
			return true;
		}
		else if (myAccount.bet < myGuessingGameLow.GetBetMinimum())
		{
			std::cout << "\nYour bet is lower than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameLow.GetBetMinimum(), myGuessingGameLow.GetBetMaximum());
			return true;
		}
	}
	else if (myStakes == Stakes::High)
	{
		if (myAccount.money < myGuessingGameHigh.GetBetMinimum())
		{
			std::cout << "\nYou dont have enough credit for this table anymore\n";
			myStakes = Stakes::None;
			system("pause");
			EnterMainMenu();
		}
		if (myAccount.money < myAccount.bet)
		{
			std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
			return true;
		}
		else if (myAccount.bet > myGuessingGameHigh.GetBetMaximum())
		{
			std::cout << "\nYour bet is higher than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
			return true;
		}
		else if (myAccount.bet < myGuessingGameHigh.GetBetMinimum())
		{
			std::cout << "\nYour bet is lower than what is allowed at this table! Please change bet amount.\n";
			ChangeBetInRange(myGuessingGameHigh.GetBetMinimum(), myGuessingGameHigh.GetBetMaximum());
			return true;
		}
	}
	return false;
}

bool Casino::HandleBankruptcy()
{
	if (myAccount.money <= 0)
	{
		std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
		std::cout << "\nYou leave with: " << myAccount.money << "kr.";
		myCurrentTable = TableOption::Quit;
		myStakes = Stakes::None;
		std::cin.clear();
		std::cin.ignore(CIN_IGNORE_MAX, '\n');
		return true;
	}
	if (myAccount.money < myAccount.bet && myCurrentTable != TableOption::Quit && myCurrentTable != TableOption::GuessingGame)
	{
		std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
		ChangeBet();
	}
	return false;
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
	constexpr int statArrSize = sizeof(ourStatArr) / sizeof(int);

	int statArrTemp[statArrSize] = {};

	for (int i = 0; i < statArrSize; i++)
	{
		statArrTemp[i] = ourStatArr[i]; //make a copy array
	}

	for (int i = 0; i < statArrSize - 1; i++)
	{
		if (ourStatArr[0] == ResultToIndex(Result::Empty))
		{
			break; //free spot
		}
		ourStatArr[i + 1] = statArrTemp[i]; // move all indexes to the left [W][L][L][L][W] -> [0][W][L][L][L]
	}

	arrIndex = 0;

	if (aIsWin)
	{
		ourStatArr[arrIndex] = ResultToIndex(Result::Win);
	}
	else
	{
		ourStatArr[arrIndex] = ResultToIndex(Result::Loss);
	}

	ShowStats(ourStatArr);
}

int Casino::RollDice()
{
	return GenerateRandomNumber(DICE_MIN, DICE_MAX);
}

bool Casino::EvaluateTableEarnings(const int aMoneyEarnedAtTable) const
{
	bool wonTooMuch = false;
	bool shouldQuit = true;
	int earningsMax = myEarningsMax;
	int LossesMax = myLossesMax;

	if (myStakes == Stakes::Low)
	{
		earningsMax = myEarningsMax + myGuessingGameLow.GetBetMaximum();
		LossesMax = myLossesMax - myGuessingGameLow.GetBetMaximum();
	}
	else if (myStakes == Stakes::High)
	{
		earningsMax = myEarningsMax + myGuessingGameHigh.GetBetMaximum();
		LossesMax = myLossesMax - myGuessingGameHigh.GetBetMaximum();
	}

	if (myCurrentTable == TableOption::Quit)
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



