#include "pch.h"
#include "CppUnitTest.h"
#include "UtilityFunctions.h"
#include <cassert>
#include <unordered_map>

// Hack to cause assert to throw exceptions
// Allows the error to be validated rather than causing the program to crash.
#define _wassert(...) AssertOveride()

#include "FixedVector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//#define ENABLE_VG_TESTS

using namespace CommonUtilies;

void AssertOveride()
{
	throw "Assert Failed";
}


namespace FixedVectorTests
{
	TEST_CLASS(FixedVectorBasicTypeTests)
	{
	public:
		
		TEST_METHOD(SizeIsZeroAfterConstruction)
		{
			FixedVector<int, 1> v;
			Assert::AreEqual(0u, v.size());
			Assert::AreEqual(1u, v.capacity());
			Assert::IsTrue(v.empty());
		}

		TEST_METHOD(AddOneElement)
		{
			FixedVector<int, 1> v;
			v.push_back(1);
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(1u, v.size());
			Assert::IsFalse(v.empty());
		}

		TEST_METHOD(AddInCorrectOrder)
		{
			FixedVector<int, 10> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			for (int i = 0; i < 10; ++i)
			{
				Assert::AreEqual(v[i], i);

			}
			Assert::AreEqual(10u, v.size());
		}

		TEST_METHOD(RangeFor)
		{
			FixedVector<int, 10> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			int i = 0;
			for (int value : v)
			{
				Assert::AreEqual(value, i);
				i++;
			}
		}

		TEST_METHOD(CompareAt)
		{
			FixedVector<int, 7> vectorOfNumbers;
			for (int i = 0; i < 7; i++)
			{
				vectorOfNumbers.push_back(i);
			}

			for (int i = 0; i < 7; i++)
			{
				Assert::AreEqual(i, vectorOfNumbers.at(i));
			}
		}

		TEST_METHOD(Assert_AtOutOfBoundsHigh)
		{
			try
			{
				FixedVector<int, 10> s;
				s.at(99);
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_AtOutOfBoundsLow)
		{
			try
			{
				FixedVector<int, 10> s;
				s.at(-99);
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(EqualOperator)
		{
			FixedVector<int, 10> vectorOfNumbers;
			for (int i = 0; i < 10; ++i)
			{
				vectorOfNumbers.push_back(i);
			}

			FixedVector<int, 10> copiedVectorOfNumbers;
			copiedVectorOfNumbers = vectorOfNumbers;

			for (int i = 0; i < 10; ++i)
			{
				Assert::AreEqual(vectorOfNumbers[i], copiedVectorOfNumbers[i]);
			}
			Assert::IsTrue(copiedVectorOfNumbers.size() == vectorOfNumbers.size());
		}

		TEST_METHOD(CopyConstructorWithSafeMode)
		{
			FixedVector<int, 10> vectorOfNumbers;
			for (int i = 0; i < 10; ++i)
			{
				vectorOfNumbers.push_back(i);
			}

			FixedVector<int, 10> copiedVectorOfNumbers(vectorOfNumbers);

			for (int i = 0; i < 10; ++i)
			{
				Assert::AreEqual(vectorOfNumbers[i], copiedVectorOfNumbers[i]);
			}
			Assert::IsTrue(copiedVectorOfNumbers.size() == vectorOfNumbers.size());
		}

		TEST_METHOD(EraseFirst)
		{
			FixedVector<int, 10> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			v.erase(v.begin());
			Assert::IsTrue(v[0] == 1);
			Assert::IsTrue(v[1] == 2);
		}

		TEST_METHOD(EraseLast)
		{
			FixedVector<int, 10> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			v.erase(v.end() - 1);
			Assert::IsTrue(v[8] == 8);
			Assert::AreEqual(9u, v.size());
		}

		TEST_METHOD(InsertFirst)
		{
			FixedVector<int, 20> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			int value = 99;

			v.insert(v.begin(), value);
			Assert::IsTrue(v[0] == value);
			Assert::IsTrue(v[1] == 0);
			Assert::IsTrue(v[10] == 9);
		}

		TEST_METHOD(InsertLast)
		{
			FixedVector<int, 20> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			int value = 99;

			v.insert(v.end(), value);
			Assert::IsTrue(v[10] == value);
			Assert::IsTrue(v[9] == 9);
			Assert::IsTrue(v.size() == 11);
		}

		TEST_METHOD(InsertIfEmptyIsAllowed)
		{
			FixedVector<int, 10> v;
			v.insert(v.begin(), 123);
			Assert::AreEqual(123, v[0]);
			Assert::IsTrue(v.size() == 1);
		}

		TEST_METHOD(InsertInMiddle)
		{
			FixedVector<int, 20, int> v;
			int value = 99;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			v.insert(v.begin() + 5, value);
			Assert::IsTrue(v[4] == 4);
			Assert::IsTrue(v[5] == value);
			Assert::IsTrue(v[6] == 5);
			Assert::IsTrue(v[10] == 9);
			Assert::IsTrue(v.size() == 11);
		}

		TEST_METHOD(SizeIsZeroAfterClear)
		{
			FixedVector<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.push_back(i);
			}

			s.clear();
			Assert::AreEqual(0u, s.size());
		}

		TEST_METHOD(PopBack)
		{
			FixedVector<int, 10> v;
			for (int i = 0; i < 10; ++i)
			{
				v.push_back(i);
			}

			v.pop_back();

			Assert::AreEqual(9u, v.size());
		}

		TEST_METHOD(Resize)
		{
			FixedVector<int, 10> s;
			s.resize(5, 1);

			Assert::AreEqual(5u, s.size());

			for (int i = 0; i < 5; ++i)
			{
				Assert::AreEqual(1, s[i]);
			}
		}

		TEST_METHOD(ResizeEmpty)
		{
			FixedVector<int, 10> s;
			s.resize(5, 1);

			Assert::AreEqual(5u, s.size());

			for (int i = 0; i < 5; ++i)
			{
				Assert::AreEqual(1, s[i]);
			}
		}

		TEST_METHOD(ResizeLower)
		{
			FixedVector<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.push_back(i);
			}
			s.resize(5);

			Assert::AreEqual(5u, s.size());

			for (int i = 0; i < 5; ++i)
			{
				Assert::AreEqual(i, s[i]);
			}
		}

		TEST_METHOD(ResizeHigher)
		{
			FixedVector<int, 20> s;
			for (int i = 0; i < 10; ++i)
			{
				s.push_back(i);
			}
			s.resize(15, 1);

			Assert::AreEqual(15u, s.size());

			for (int i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, s[i]);
			}

			for (int i = 10; i < 15; ++i)
			{
				Assert::AreEqual(1, s[i]);
			}
		}

#ifdef _DEBUG

		TEST_METHOD(Assert_SubscriptOutOfBounds)
		{
			try
			{
				FixedVector<int, 10> s;
				s[9] = 10;
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_AddTooMuch)
		{
			try
			{
				FixedVector<int, 10> s;
				for (int i = 0; i < 999; i++)
				{
					s.push_back(i);
				}
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_SubscriptOutOfBoundsNegativeValue)
		{
			try
			{
				FixedVector<int, 10> s;
				s[-99] = 10;
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_SizeIsZeroAfterClear)
		{
			try
			{
				FixedVector<int, 10> s;
				s.push_back(1);
				s.clear();
				s[0] = 10;
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_EraseIndexOutOfBoundsHigh)
		{
			try
			{
				FixedVector<int, 10> s;
				s.erase(s.begin() + 10);
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_EraseValueOutOfBoundsLow)
		{
			try
			{
				FixedVector<int, 10> s;
				s.erase(s.begin() - 1);
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_InsertOutOfBoundsHigh)
		{
			try
			{
				int value = 99;
				FixedVector<int, 10> s;
				s.insert(s.end()+1, value);
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_InsertOutOfBoundsLow)
		{
			try
			{
				int value = 99;
				FixedVector<int, 10> s;
				s.insert(s.begin() - 1, value);
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}
	
		TEST_METHOD(Assert_Front)
		{
			FixedVector<int, 10> s;
			s.push_back(2);
			s.push_back(4);
			int& front = s.front();
			Assert::IsTrue(front == 2);
			front = 4;
			Assert::IsTrue(s.front() == 4);
		}

		TEST_METHOD(Assert_FrontWhenEmpty)
		{
			try
			{
				FixedVector<int, 10> s;
				s.front();
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}

		TEST_METHOD(Assert_Back)
		{
			FixedVector<int, 10> s;
			s.push_back(2);
			s.push_back(4);
			int& back = s.back();
			Assert::IsTrue(back == 4);
			back = 7;
			Assert::IsTrue(s.back() == 7);
		}

		TEST_METHOD(Assert_BackWhenEmpty)
		{
			try
			{
				FixedVector<int, 10> s;
				s.back();
				Assert::Fail();
			}
			catch (const char* assertMsg)
			{
				(assertMsg);
			}
		}
#endif
	};

#ifdef ENABLE_VG_TESTS

	struct CallStatistics
	{
		struct ObjectStats
		{
			int constructionCalls;
			int destructionCalls;
		};

		int constructorCalls;
		int destructorCalls;

		std::unordered_map<void*, ObjectStats> objectStats;
	};

	void ValidateObjectStatistics(const CallStatistics& aCallStats)
	{
		for (const auto& pair : aCallStats.objectStats)
		{
			Assert::AreEqual(pair.second.constructionCalls, pair.second.destructionCalls);
		}

	}

	struct FunctionCallCounter
	{
		static CallStatistics statistics;

		FunctionCallCounter() 
		{
			statistics.constructorCalls++; 
			statistics.objectStats[this].constructionCalls++;
		}
		FunctionCallCounter(const FunctionCallCounter&) 
		{ 
			statistics.constructorCalls++; 
			statistics.objectStats[this].constructionCalls++;
		}

		~FunctionCallCounter() 
		{ 
			statistics.destructorCalls++; 
			statistics.objectStats[this].destructionCalls++;
		}
		FunctionCallCounter& operator=(const FunctionCallCounter&) { return *this; }
	};

	CallStatistics FunctionCallCounter::statistics;

	TEST_CLASS(FixedVectorComplexTypesTests)
	{
	public:


		TEST_METHOD(NoConstructorCalledIfEmpty)
		{
			FunctionCallCounter::statistics = {};

			{
				FixedVector<FunctionCallCounter, 10> s;
			}

			Assert::AreEqual(0, FunctionCallCounter::statistics.constructorCalls);
			Assert::AreEqual(0, FunctionCallCounter::statistics.destructorCalls);
			ValidateObjectStatistics(FunctionCallCounter::statistics);
		}

		TEST_METHOD(DestructorCalledOnElements)
		{
			FunctionCallCounter::statistics = {};
			{
				FixedVector<FunctionCallCounter, 10> s;

				s.push_back(FunctionCallCounter());

				// clear out statistics after adding, to only count destructor call
				FunctionCallCounter::statistics.constructorCalls = 0;
				FunctionCallCounter::statistics.destructorCalls = 0;
			}

			Assert::AreEqual(0, FunctionCallCounter::statistics.constructorCalls);
			Assert::AreEqual(1, FunctionCallCounter::statistics.destructorCalls);
			ValidateObjectStatistics(FunctionCallCounter::statistics);
		}

		TEST_METHOD(PushBackCallsCopy)
		{
			FunctionCallCounter::statistics = {};

			{
				FixedVector<FunctionCallCounter, 10> s;

				s.push_back(FunctionCallCounter());

			}
			ValidateObjectStatistics(FunctionCallCounter::statistics);
		}

		TEST_METHOD(EraseCallsAssignOrCopy)
		{
			FunctionCallCounter::statistics = {};

			{
				FixedVector<FunctionCallCounter, 10> s;

				s.push_back(FunctionCallCounter());
				s.push_back(FunctionCallCounter());

				s.erase(s.begin());
			}

			ValidateObjectStatistics(FunctionCallCounter::statistics);
		}
	};

#endif
}
