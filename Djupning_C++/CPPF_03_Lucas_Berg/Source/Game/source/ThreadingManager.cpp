#include "ThreadingManager.h"
#include "CommonUtilities/Timer.h"
#include <chrono>

ThreadingManager::ThreadingManager()
{
}

ThreadingManager::~ThreadingManager()
{
	StopLogicThread();
}

void ThreadingManager::StartLogicThread(const std::function<void(float)> aUpdateCallback)
{
	myUpdateCallback = aUpdateCallback;
	myRunning = true;
	myLogicThread = std::thread(&ThreadingManager::LogicThreadLoop, this);
}

void ThreadingManager::StopLogicThread()
{
	if (myRunning)
	{
		myRunning = false;

		{
			std::lock_guard<std::mutex> lock(mySwapMutex);
			myRenderDone = true;
		}
		myRenderFinished.notify_one();

		if (myLogicThread.joinable())
		{
			myLogicThread.join();
		}
	}
}

void ThreadingManager::LogicThreadLoop()
{
	CommonUtilities::Timer timer;

	while (myRunning)
	{
		timer.Update();

		{
			std::unique_lock<std::mutex> lock(mySwapMutex);
			myRenderFinished.wait(lock, [this] { return myRenderDone || !myRunning; });

			if (!myRunning)
			{
				break;
			}
			myRenderDone = false;
			myUpdateDone = false;
		}

		// for testing: sleep to fake slow logic thread
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));

		if (myUpdateCallback)
		{
			myUpdateCallback(timer.GetDeltaTime());
		}

		{
			std::lock_guard<std::mutex> lock(mySwapMutex);
			myUpdateDone = true;
		}
		myUpdateFinished.notify_one();
	}
}

void ThreadingManager::SyncAndSwap(const std::function<void()> aSwapCallback)
{
	std::unique_lock<std::mutex> lock(mySwapMutex);
	myUpdateFinished.wait(lock, [this] { return myUpdateDone; });

	aSwapCallback();

	myUpdateDone = false;
}


void ThreadingManager::SignalUpdateDone()
{
	std::lock_guard<std::mutex> lock(mySwapMutex);
	myUpdateDone = true;
	myUpdateFinished.notify_one();
}

void ThreadingManager::SignalRenderDone()
{
	std::lock_guard<std::mutex> lock(mySwapMutex);
	myRenderDone = true;
	myRenderFinished.notify_one();
}
