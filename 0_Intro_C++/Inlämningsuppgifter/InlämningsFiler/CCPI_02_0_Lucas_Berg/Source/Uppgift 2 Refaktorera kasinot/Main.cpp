#include "Enums.h"
#include "Structs.h"
#include "Print.h"
#include "Menu.h"

#include <iostream>
#include <random>

int main()
{
	using namespace Print;
	using namespace Menu;

	Account account = {};
	Table table = {};

	table.statArr; 
	table.moneyArr;

	ShowIntro(account);
	MainMenu(account, table);
	return 0;
}
