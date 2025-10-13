// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Diablo.h"
#include "ConsoleUI.h"

int main()
{
	Diablo diablo = Diablo();
	diablo.RunDiablo();
	ConsoleUI::Pause();
}

