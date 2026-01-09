// TimerTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Timer.h"
#include <iostream>
#include <thread>

using namespace CommonUtilities;

int main()
{
	Timer timer;
	timer.Start();

	while (true)
	{
		timer.Update();
		std::cout << "DeltaTime: " << timer.GetDeltaTime();
		std::cout << " Total time: " << timer.GetTotalTime() << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}
