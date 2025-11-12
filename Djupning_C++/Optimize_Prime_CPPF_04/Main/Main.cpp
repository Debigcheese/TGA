#include <future>
#include <iostream>
#include <chrono>

using namespace std;

static atomic<bool> stopFlag{false};
static atomic<uint64_t> nextCandidate{3};
static mutex outMx;

static inline bool isPrime(int n)
{
	if (n < 2)
	{
		return false;
	}
	if (n % 2 == 0)
	{
		return n == 2;
	}
	if (n % 3 == 0)
	{
		return n == 3;
	}
	for (int i = 5; 1LL * i * i <= n; i += 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	cout << "Skriver primtal på 8 trådar. Tryck Enter för att avsluta.\n";

	thread inputThread([]
	{
		cin.get();
		stopFlag.store(true, memory_order_relaxed);
	});

	{
		lock_guard<mutex> lock(outMx);
		cout << 2 << '\n';
	}

	const int THREADS = 8;
	vector<thread> workers;
	workers.reserve(THREADS);

	for (int t = 0; t < THREADS; ++t)
	{
		workers.emplace_back([]
		{
			while (!stopFlag.load(memory_order_relaxed))
			{
				uint64_t n = nextCandidate.fetch_add(2, memory_order_relaxed);
				if (isPrime(n))
				{
					lock_guard<mutex> lock(outMx);
					cout << n << '\n';
				}
			}
		});
	}

	for (auto& thread : workers)
	{
		thread.join();
	}
	inputThread.join();

	cout << "Avslutar.\n";
	return 0;
}
