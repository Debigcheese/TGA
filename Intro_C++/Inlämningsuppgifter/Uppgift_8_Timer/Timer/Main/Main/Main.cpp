#include <iostream>
#include <thread>

#include "Timer.h"

using namespace CommonUtilities;

int main(int argc, char* argv[])
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
