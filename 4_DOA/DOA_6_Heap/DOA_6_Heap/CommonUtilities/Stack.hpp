#pragma once

#include <vector>
#include <cassert>

namespace CommonUtilities
{
	template <class T>
	class Stack
	{
	public:
		//Skapar en tom stack
		Stack() : myStack()
		{
		}

		//Returnerar antal element i stacken
		int GetSize() const
		{
			return (int)myStack.size();
		}

		//Returnerar det översta elementet i stacken. Kraschar med en assert om
		//stacken är tom.
		const T& GetTop() const
		{
			assert(!myStack.empty() && "GetTop(): stack is empty, cant access first element");
			return myStack.back();
		}

		//Returnerar det översta elementet i stacken. Kraschar med en assert om
		//stacken är tom.
		T& GetTop()
		{
			assert(!myStack.empty() && "GetTop(): stack is empty, cant access first element");
			return myStack.back();
		}

		//Lägger in ett nytt element överst på stacken
		void Push(const T& aValue)
		{
			myStack.push_back(aValue);
		}

		//Tar bort det översta elementet från stacken och returnerar det. Kraschar
		//med en assert om stacken är tom.
		T Pop()
		{
			assert(!myStack.empty() && "Pop: stack is empty, cant access first element");
			auto target = myStack.back();
			myStack.pop_back();
			return target;
		}

	private:
		std::vector<T> myStack;
	};
}
