#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <chrono>

#include "Shared/Utility.h"
#include "Student Code/Vector2.h"

/// <summary>
/// This is a hack to emulate the TGA vector for the task of convertion
/// It only works because they happen to have the same name
/// </summary>
namespace Tga
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2() : x(T(0)), y(T(0))
		{
		}

		Vector2(const T aX, const T aY) : x(aX), y(aY)
		{
		}

		Vector2(const Vector2<T>&) = default;
		Vector2& operator=(const Vector2&) = default;
	};
}

/// <summary>
/// To make the test-code cleaner we have a shorthand way to refer to the types
/// where the tga-vectors are prefixed Tga.
/// All the shorthands are post-fixed with the dimentionality as a number.
/// Along with the type as a one char shortened version, so for example it identifies:
/// float as 'f', int as 'i' or double as 'd'
/// </summary>
using TgaVectorf = Tga::Vector2<float>;
using TgaVectord = Tga::Vector2<double>;
using TgaVectori = Tga::Vector2<int>;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Vector2f = CommonUtilities::Vector2<float>;
using Vector2d = CommonUtilities::Vector2<double>;
using Vector2i = CommonUtilities::Vector2<int>;

namespace Vectors
{
	TEST_CLASS(Vector2Test)
	{
	public:
		// Testing if all neccessary const:s are declared
		TEST_METHOD(V2_Const)
		{
		}

		TEST_METHOD(V2_Size)
		{
		}

		TEST_METHOD(V2_Default_Constructor)
		{
		}

		TEST_METHOD(V2_Constructor)
		{
		}

		// Compiler generated version as stated in the assignment description, test included for reference and completeness
		TEST_METHOD(V2_Copy_Constructor)
		{
		}

		// Compiler generated version as stated in the assignment description, test included for reference and completeness
		TEST_METHOD(V2_Assignment)
		{
		}

		TEST_METHOD(V2_ToTGAConvertion)
		{
		}

		TEST_METHOD(V2_ToOtherTypeConvertion)
		{
		}

		TEST_METHOD(V2_Negation)
		{
		}

		TEST_METHOD(V2_Addition)
		{
		}

		TEST_METHOD(V2_Subtraction)
		{
		}

		TEST_METHOD(V2_Scalar_Multiplication)
		{
		}

		TEST_METHOD(V2_Length)
		{
		}

		TEST_METHOD(V2_LengthSqrOptimize)
		{
		}

		TEST_METHOD(V2_Unit_Vector_Length)
		{
		}

		TEST_METHOD(V2_Normalise)
		{
		}

		TEST_METHOD(V2_Length_Zero_Vector)
		{
		}

		TEST_METHOD(V2_Normalise_Zero_Vector)
		{
		}

		TEST_METHOD(V2_Component_Multiplication)
		{
		}

		TEST_METHOD(V2_Dot)
		{
		}

	private:
		static const float ourToleranceF;
		static const double ourToleranceD;
	};

	const float Vector2Test::ourToleranceF = 0.00001f;
	const double Vector2Test::ourToleranceD = 0.00001;
}
