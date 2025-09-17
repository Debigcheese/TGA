#include "Print.h"
#include <iostream>

namespace Print
{
	void PrintIntro()
	{
		std::cout << "Welcome to Diablo\n";
		system("pause");
	}
	void PrintUI()
	{
	}
	void PrintMainMenu()
	{
		std::cout
			<< "\n<--- Main Menu --->\n"
			<< "1) Play game\n"
			<< "2) Activate cheats\n"
			<< "Choice: ";
	}
}
