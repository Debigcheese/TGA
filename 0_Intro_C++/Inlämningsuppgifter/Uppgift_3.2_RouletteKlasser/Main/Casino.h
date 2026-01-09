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
	void ValidateBet();
	bool EvaluateTableEarnings(const int aMoneyEarnedAtTable) const;
	bool HandleBankruptcy();

	static int Payout(Account& aAccount, const int aPayoutAmount);
	static int DeductBet(Account& aAccount);
	static void UpdateStats(bool aIsWin);

private:
	//Account
	const int DEFAULT_MONEY = 555000;
	const int DEFAULT_BET = 1000;
	const TableOption DEFAULT_TABLE = TableOption::Menu;
	const Stakes DEFAULT_STAKES = Stakes::None;

	//stat
	static const int STAT_ARRAY_SIZE = 5;
	const int EARNINGS_MAX = 30000;
	const int LOSSES_MAX = -20000;

	//name
	static const int NAME_ARRAY_SIZE = 18;
	const int NAME_SIZE_MIN = 2;
	const int NAME_SIZE_MAX = 16;

	const int ZERO_INDEX = 0;
	const int ENUM_TO_INDEX_OFFSET = 1;

	//GUESSING GAME STAKE
	const int GUESSING_GAME_STAKE_LOW_MIN = 1;
	const int GUESSING_GAME_STAKE_LOW_MAX = 1000;
	const int GUESSING_GAME_STAKE_HIGH_MIN = 1000;
	const int GUESSING_GAME_STAKE_HIGH_MAX = 100000;

	const int CIN_IGNORE_MAX = 10000;

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
