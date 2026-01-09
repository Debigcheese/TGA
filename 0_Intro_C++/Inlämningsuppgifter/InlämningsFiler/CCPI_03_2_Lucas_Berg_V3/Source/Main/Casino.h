#pragma once
#include "Structs.h"
#include "Enums.h"

#include "GuessingGame.h"
#include "OddOrEvenGame.h"
#include "SpinTheWheel.h"
#include "HigherOrLower.h"
#include "RouletteGame.h"

class Casino
{
public:
	Casino();
	void InitCasino();
	void RunCasino();

	void ReadPlayerName() const;
	static const char* GetPlayerName();

	void EnterMainMenu();
	void EnterTable();
	void ChooseTableStakes();

	static const int* GetStatArr();
	static int GetStatArrSize();
	void ChangeBet();
	void ChangeBetInRange(const int aBetMin, int aBetMax);
	bool ValidateBet();
	bool EvaluateTableEarnings(const int aMoneyEarnedAtTable) const;
	bool HandleBankruptcy();

	static int Payout(Account& aAccount, const int aPayoutAmount);
	static int DeductBet(Account& aAccount);
	static void UpdateStats(bool aIsWin);

	static int RollDice();

private:
	
	//Account
	const int myDefaultMoney = 155000;
	const int myDefaultBet = 1000;
	const TableOption myDefaultTable = TableOption::Menu;
	const Stakes myDefaultStakes = Stakes::None;

	//stat
	static const int STAT_ARRAY_SIZE = 5;
	const int myEarningsMax = 30000;
	const int myLossesMax = -20000;

	//name
	static const int NAME_ARRAY_SIZE = 18;
	static const int NAME_SIZE_MIN = 2;
	static const int NAME_SIZE_MAX = 16;

	//GUESSING GAME STAKE
	static const int GUESSING_GAME_STAKE_LOW_MIN = 1;
	static const int GUESSING_GAME_STAKE_LOW_MAX = 1000;
	static const int GUESSING_GAME_STAKE_HIGH_MIN = 1000;
	static const int GUESSING_GAME_STAKE_HIGH_MAX = 100000;

	static char ourName[NAME_ARRAY_SIZE];
	static int ourStatArr[STAT_ARRAY_SIZE];
	Account myAccount;
	TableOption myCurrentTable;
	Stakes myStakes;

	GuessingGame myGuessingGameLow;
	GuessingGame myGuessingGameHigh;
	OddOrEvenGame myOddOrEven;
	SpinTheWheel mySpinTheWheel;
	HigherOrLower myHigherOrLower;
	RouletteGame myRoulette;
};
