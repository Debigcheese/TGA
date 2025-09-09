#pragma once
#include "Structs.h"
#include "Enums.h"

namespace TableFunctions
{
	void ChangeBet(Account& account);
	void UpdateStats(Table& table, bool isWin);
	void EnterTable(Account& account, Table& table);
	void EvaluateTableEarnings(Account& account, Table& table);
	void HandleBankruptcy(Account& account, Table& table);
}