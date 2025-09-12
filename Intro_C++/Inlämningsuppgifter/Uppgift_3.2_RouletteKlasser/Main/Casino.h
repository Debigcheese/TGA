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

	void MainMenu();
	void EnterTable();

	static const int* GetStatArr();
	void ChangeBet();
	bool EvaluateTableEarnings(const int moneyEarnedAtTable) const;
	void HandleBankruptcy();

	static int Payout(Account& account, int payoutAmount);
	static int DeductBet(Account& account);
	static void UpdateStats(bool isWin);

private:
	Account account;
	TableOption currentTable = CONSTANTS::DEFAULT_TABLE;
	static int statArr[CONSTANTS::STAT_ARRAY_SIZE];

	GuessingGame myGuessingGame;
	OddOrEvenGame myOddOrEven;
	SpinTheWheel mySpinTheWheel;
	HigherOrLower myHigherOrLower;
	RouletteGame myRoulette;

};

