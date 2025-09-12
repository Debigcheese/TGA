#pragma once
#include "Structs.h"
#include "Enums.h"

namespace Print
{
	// Print to console
	void ShowIntro(const Account& account);
	void ShowPersonalDetails(const Account& account, const int statArr[]);
	void ShowOptions(const TableOption& currentTable);
	void ShowRules(const TableOption& currentTable);
	void ShowStats(const int statArr[]);
}
