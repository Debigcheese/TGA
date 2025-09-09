#include "Menu.h"
#include "Print.h"
#include "Helpers.h"
#include "Games.h"
#include "TableFunctions.h"

#include <iostream>

namespace Menu
{
	using namespace Helpers;
	using namespace Print;
	using namespace TableFunctions;
	using namespace Games;

	void MainMenu(Account& account, Table& table)
	{
		table.currentTable = TableOption::Menu;

		while (table.currentTable == TableOption::Menu)
		{

			ShowPersonalDetails(account);
			ShowOptions(table);
			HandleBankruptcy(account, table);

			TableOption chosenTable = static_cast<TableOption>(ReadIntInRange(//reads 1-5
				TableToIndex(TableOption::GuessingGame),
				5)); // FIX

			switch (chosenTable)
			{
			case TableOption::GuessingGame:
			{
				table.currentTable = TableOption::GuessingGame;
				EnterTable(account, table);
				break;
			}
			case TableOption::OddOrEven:
			{
				table.currentTable = TableOption::OddOrEven;
				EnterTable(account, table);
				break;
			}
			case TableOption::SpinTheWheel:
			{
				table.currentTable = TableOption::SpinTheWheel;
				EnterTable(account, table);
				break;
			}
			case TableOption::Stats:
			{
				ShowStats(table);
				system("pause");
				break;
			}
			case TableOption::Quit:
			{
				std::cout << "\nYou leave with " << account.money << " kr. Come back soon!\n";
				table.currentTable = TableOption::Quit;
				break;
			}
			default: break;
			}
			//if (table.currentTable != TableOption::Quit)
			//{
			//	EnterTable(account, table);
			//}

		}
	}
}