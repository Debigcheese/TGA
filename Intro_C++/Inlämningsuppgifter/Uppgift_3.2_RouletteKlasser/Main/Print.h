#pragma once
#include "Structs.h"
#include "Enums.h"

namespace Print
{
	// Print to console
	void ShowIntro(const Account& aAccount);
	void ShowPersonalDetails(const Account& aAccount, const int aStatArr[], const char* aName);
	void ShowOptions(const TableOption& aCurrentTable);
	void ShowRules(const TableOption& aCurrentTable);
	void ShowStats(const int aStatArr[]);
	void ShowName(const char* aName);
}
