#pragma once
#include <cassert>
#include <vector>

namespace CommonUtilities
{
	template <class T>
	class Queue
	{
	public:
		//Skapar en tom kö
		Queue() : myQueue()
		{
		}

		//Returnerar antal element i kön
		int GetSize() const
		{
			return (int)myQueue.size();
		}

		//Returnerar elementet längst fram i kön. Kraschar med en assert om kön är 
		//tom
		const T& GetFront() const
		{
			assert(!myQueue.empty() && "GetFront(): Cant use front if Queue is empty");
			return myQueue.front();
		}

		//Returnerar elementet längst fram i kön. Kraschar med en assert om kön är 
		//tom
		T& GetFront()
		{
			assert(!myQueue.empty() && "GetFront(): Cant use front if Queue is empty");
			return myQueue.front();
		}

		//Lägger in ett nytt element längst bak i kön
		void Enqueue(const T& aValue)
		{
			myQueue.push_back(aValue);
		}

		//Tar bort elementet längst fram i kön och returnerar det. Kraschar med en 
		//assert om kön är tom.
		T Dequeue()
		{
			assert(!myQueue.empty() && "Dequeue(): Cant use Dequeue if Queue is empty");
			auto target = myQueue.front();
			myQueue.erase(myQueue.begin());
			return target;
		}

	private:
		std::vector<T> myQueue;
	};
}
