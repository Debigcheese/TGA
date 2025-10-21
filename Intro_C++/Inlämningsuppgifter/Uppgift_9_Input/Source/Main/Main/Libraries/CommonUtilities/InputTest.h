#pragma once
#include <iostream>
#include "InputHandler.h"
#include "Print.h"
#include <Windows.h>

namespace InputTests
{
	using input = CommonUtilities::InputHandler;

	// global referenser (delas med main)
	extern input* myInputHandler;
	extern HWND myMainWindowHandle;
	extern bool myMouseLocked;

	void PrintInstructions();
	void RunTests();
}
