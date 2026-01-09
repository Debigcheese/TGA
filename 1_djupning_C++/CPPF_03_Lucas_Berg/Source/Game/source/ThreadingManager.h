#pragma once
#include <functional>
#include <mutex>

class ThreadingManager
{
public:
	ThreadingManager();
	~ThreadingManager();

	void StartLogicThread(std::function<void(float)> aUpdateCallback);
	void StopLogicThread();

	void SyncAndSwap(std::function<void()> aSwapCallback);
	void SignalUpdateDone();
	void SignalRenderDone();

private:
	void LogicThreadLoop();

	std::thread myLogicThread;
	std::atomic<bool> myRunning{false};

	std::mutex mySwapMutex;
	std::condition_variable myUpdateFinished;
	std::condition_variable myRenderFinished;
	bool myUpdateDone = false;
	bool myRenderDone = true;

	std::function<void(float)> myUpdateCallback;
};
