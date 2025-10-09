#pragma once
#include <algorithm>
#include <assert.h>

/// <summary>
/// Implements a class with similar interface to std::vector, but stores data
/// inlined in the class with a fixed storage capacity.
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <typeparam name="SizeType"></typeparam>
/// <typeparam name="CAPACITY"></typeparam>
/// 
template <typename Type, unsigned int CAPACITY, typename SizeType = unsigned int>
class FixedVector
{
public:
	typedef Type* iterator;
	typedef const Type* const_iterator;

	FixedVector() : mySize(0), myStorage{}
	{
	}

	FixedVector(const FixedVector& aFixedVector) : mySize(aFixedVector.mySize)
	{
		for (SizeType i = 0; i < mySize; ++i)
		{
			myStorage[i] = aFixedVector[i];
		}
	}

	~FixedVector()
	{
		clear();
	}

	//<--- loops n elements in order to copy a vector O(n) --->
	FixedVector& operator=(const FixedVector& aFixedVector)
	{
		if (this == &aFixedVector)
		{
			return *this;
		}
		mySize = aFixedVector.mySize;
		for (SizeType i = 0; i < mySize; ++i)
		{
			myStorage[i] = aFixedVector[i];
		}
		return *this;
	}

	Type& front()
	{
		assert(mySize > 0);
		return myStorage[0];
	}

	const Type& front() const
	{
		assert(mySize > 0);
		return myStorage[0];
	}

	Type& back()
	{
		assert(mySize > 0);
		return myStorage[mySize - 1];
	}

	const Type& back() const
	{
		assert(mySize > 0);
		return myStorage[mySize - 1];
	}

	Type& at(SizeType aIndex)
	{
		assert(mySize > aIndex);
		return myStorage[aIndex];
	}

	const Type& at(SizeType aIndex) const
	{
		assert(mySize > aIndex);
		return myStorage[aIndex];
	}

	const Type& operator[](SizeType aIndex) const
	{
		assert(mySize > aIndex);
		return myStorage[aIndex];
	}

	Type& operator[](SizeType aIndex)
	{
		assert(mySize > aIndex);
		return myStorage[aIndex];
	}

	//	assert(mySize > 0);
	//Type storageTemp = myStorage;
	//for (int i = 0; i < mySize; ++i)
	//{
	//	myStorage[i + 1] = storageTemp[i];
	//}
	//myStorage[0] = aObject;

	//<--- places 1 element at the end of the list O(1) --->
	void push_back(const Type& aObject)
	{
		assert(mySize < capacity() && "push_back on full capacity FixedVector");
		++mySize;
		myStorage[mySize] = aObject;
	}

	//<--- insert element at position --->
	void insert(iterator aIterator, const Type& aObject)
	{
		assert(mySize < CAPACITY && "insert on full capacity FixedVector");
		assert(aIterator >= begin() && aIterator <= end() && "insert iterator out of bounds");

		for (auto it = end(); it != aIterator; --it)
		{
			*it = std::move(*(it - 1));
		}

		*aIterator = aObject;
		++mySize;

		//SizeType idx = static_cast<SizeType>(aIterator - begin());

		//for (SizeType i = mySize; i > idx; --i) // i = mysize (mySize will index +1, like end())
		//{
		//	myStorage[i] = myStorage[i - 1]; //[3][2][1] -> [3-1][2-1][1-1]
		//}

		//myStorage[idx] = aObject;
		//++mySize;
	}

	//<--- remove element at position e.g. (myVector.begin + 3) or (it) --->
	void erase(iterator aIterator)
	{
		assert(mySize > 0 && "erase on full capacity FixedVector");
		assert(aIterator >= begin() && aIterator < end() && "erase iterator out of bounds");

		for (auto it = aIterator; (it + 1) != end(); ++it)
		{
			*it = std::move(*(it + 1));
		}

		*aIterator = Type{};
		--mySize;

		//SizeType idx = static_cast<SizeType>(aIterator - begin());

		//myStorage[mySize] = Type{};

		//for (SizeType i = idx; i + 1 < mySize; ++i)
		//{
		//	myStorage[i] = myStorage[i + 1];
		//}
		//--mySize;
		//myStorage[mySize] = Type{};
	}

	//<--- remove element at position if condition is met e.g. myVector.erase_if([](int x){ return x == 2; }); --->
	template <class Pred>
	SizeType erase_if(Pred pred)
	{
		SizeType write = 0; // where to write kept elements
		for (SizeType read = 0; read < mySize; ++read)
		{
			if (!pred(myStorage[read])) // keep element
			{
				myStorage[write++] = myStorage[read];
			}
			// else: element is dropped
		}
		SizeType removed = mySize - write;
		mySize = write; // shrink size
		return removed; // return removed
	}

	void pop_back()
	{
		assert(mySize > 0);
		--mySize;
		myStorage[mySize] = Type{};
	}

	iterator begin()
	{
		return myStorage;
	}

	const_iterator begin() const
	{
		return myStorage;
	}

	const_iterator cbegin() const
	{
		return myStorage;
	}

	//points one past last valid element
	iterator end()
	{
		return myStorage + mySize;
	}

	//points one past last valid element
	const_iterator end() const
	{
		return myStorage + mySize;
	}

	//points one past last valid element
	const_iterator cend() const
	{
		return myStorage + mySize;
	}

	void clear()
	{
		for (auto it = begin(); it != end(); ++it)
		{
			it->~T();
		}
		mySize = 0;
	}

	void resize(SizeType newSize)
	{
		mySize = newSize; // needs to be change, do tmrw
	}

	void resize(SizeType newSize, const Type& value)
	{
		mySize = newSize; //?
	}

	bool empty() const
	{
		return mySize == 0;
	}

	bool full() const
	{
		return mySize == capacity();
	}

	SizeType size() const { return mySize; }
	SizeType capacity() const { return static_cast<SizeType>(CAPACITY); }
	//emplace back & emplace?
	//write comment on the different functions
private:
	SizeType mySize;
	Type myStorage[CAPACITY]; //<- for G
	//alignas(Type) char myStorage[sizeof(Type) * CAPACITY]; // <- needed for VG
};
