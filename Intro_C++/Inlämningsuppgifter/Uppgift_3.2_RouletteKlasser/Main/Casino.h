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

	void ChangeBet();
	void UpdateStats(Table& table, bool isWin);
	bool EvaluateTableEarnings();
	void HandleBankruptcy();
	static void Payout(Account& account, Table& table, int payoutAmount);

private:
	Account account;
	Table table;

	GuessingGame myGuessingGame;
	OddOrEvenGame myOddOrEven;
	SpinTheWheel mySpinTheWheel;
	HigherOrLower myHigherOrLower;
	RouletteGame myRoulette;

};

