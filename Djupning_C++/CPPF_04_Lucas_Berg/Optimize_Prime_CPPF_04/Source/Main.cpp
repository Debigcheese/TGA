#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <map>

using namespace std;

static atomic<bool> stopFlag{false};
static atomic<uint64_t> nextCandidate{2};

static mutex outMx;

static uint64_t lastHandled = 1;
static map<uint64_t, bool> pendingResults;

static bool IsPrime(uint64_t aNumber)
{
	if (aNumber < 2)
	{
		return false;
	}
	if (aNumber % 2 == 0)
	{
		return aNumber == 2;
	}
	if (aNumber % 3 == 0)
	{
		return aNumber == 3;
	}

	for (uint64_t i = 5; i * i <= aNumber; i += 6)
	{
		if (aNumber % i == 0 || aNumber % (i + 2) == 0)
		{
			return false;
		}
	}
	return true;
}

static void HandleResult(uint64_t aNumber, bool aPrime)
{
	lock_guard<mutex> lock(outMx);

	pendingResults[aNumber] = aPrime;

	while (true)
	{
		auto it = pendingResults.find(lastHandled + 1);
		if (it == pendingResults.end())
		{
			break;
		}

		++lastHandled;
		if (it->second)
		{
			cout << lastHandled << '\n';
		}

		pendingResults.erase(it);
	}
}

int main()
{
	cout << "Press 'Enter' to start writing prime numbers\n";
	cout << "And 'Enter' again to stop\n";

	cin.get();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	thread inputThread([]
	{
		cin.get();
		stopFlag.store(true, memory_order_relaxed);
	});

	constexpr int THREADS = 8;
	vector<thread> workers;
	workers.reserve(THREADS);

	for (int t = 0; t < THREADS; ++t)
	{
		workers.emplace_back([]
		{
			while (!stopFlag.load(memory_order_relaxed))
			{
				uint64_t number = nextCandidate.fetch_add(1, memory_order_relaxed);
				bool prime = IsPrime(number);
				HandleResult(number, prime);
			}
		});
	}

	for (auto& thread : workers)
	{
		thread.join();
	}

	inputThread.join();

	{
		lock_guard<mutex> lock(outMx);
		while (!pendingResults.empty())
		{
			auto it = pendingResults.find(lastHandled + 1);
			if (it == pendingResults.end())
			{
				break;
			}

			++lastHandled;
			if (it->second)
			{
				cout << lastHandled << '\n';
			}

			pendingResults.erase(it);
		}
	}

	cout << "\nCalculation stopped, press 'Enter' to quit\n";
	cin.get();

	return 0;
}
