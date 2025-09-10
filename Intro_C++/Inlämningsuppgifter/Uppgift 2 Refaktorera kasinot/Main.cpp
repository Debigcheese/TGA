#include "Enums.h"
#include "Structs.h"
#include "Print.h"
#include "Menu.h"

#include <iostream>
#include <random>

#include "Games.h"

int main()
{
	using namespace Print;
	using namespace Menu;

	Account account = {};
	Table table = {};

	table.statArr; //stats [0] = guessing game | [1] = OddorEven | [2] = SpinTheWheel
	table.moneyArr;//money per table
	table.moneyArr[2] = +500;
	ShowIntro(account);
	MainMenu(account, table);
	return 0;
}
