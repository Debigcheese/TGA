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

	void ReadPlayerName();
	static const char* GetPlayerName();

	void MainMenu();
	void EnterTable();
	void ChooseTableStakes();

	static const int* GetStatArr();
	void ChangeBet();
	void ChangeBetInRange(const int aBetMin, int aBetMax);
	void ValidateBet();
	bool EvaluateTableEarnings(const int aMoneyEarnedAtTable) const;
	void HandleBankruptcy();

	static int Payout(Account& aAccount, const int aPayoutAmount);
	static int DeductBet(Account& aAccount);
	static void UpdateStats(bool aIsWin);

private:
	static char ourName[CONSTANTS::NAME_ARRAY_SIZE];
	Account myAccount;
	TableOption myCurrentTable = CONSTANTS::DEFAULT_TABLE;
	Stakes myStakes = CONSTANTS::DEFAULT_STAKES;
	static int ourStatArr[CONSTANTS::STAT_ARRAY_SIZE];

	GuessingGame myGuessingGameLow;
	GuessingGame myGuessingGameHigh;
	OddOrEvenGame myOddOrEven;
	SpinTheWheel mySpinTheWheel;
	HigherOrLower myHigherOrLower;
	RouletteGame myRoulette;

};

