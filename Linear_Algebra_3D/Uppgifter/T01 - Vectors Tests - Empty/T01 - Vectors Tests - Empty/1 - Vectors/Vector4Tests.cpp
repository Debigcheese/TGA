#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <chrono>

#include "Shared/Utility.h"
#include "Student Code/Vector4.h"

/// <summary>
/// This is a hack to emulate the TGA vector for the task of convertion
/// It only works because they happen to have the same name
/// </summary>
namespace Tga
{
	template<class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;
		Vector4() :x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
		Vector4(const T aX, const T aY, const T aZ, const T aW) :x(aX), y(aY), z(aZ), w(aW) {}
		Vector4(const Vector4<T>&) = default;
		Vector4& operator=(const Vector4&) = default;
	};
}

/// <summary>
/// To make the test-code cleaner we have a shorthand way to refer to the types
/// where the tga-vectors are prefixed Tga.
/// All the shorthands are post-fixed with the dimentionality as a number.
/// Along with the type as a one char shortened version, so for example it identifies:
/// float as 'f', int as 'i' or double as 'd'
/// </summary>
using TgaVectorf = Tga::Vector4<float>;
using TgaVectord = Tga::Vector4<double>;
using TgaVectori = Tga::Vector4<int>;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Vector4f = CommonUtilities::Vector4<float>;
using Vector4d = CommonUtilities::Vector4<double>;
using Vector4i = CommonUtilities::Vector4<int>;

namespace Vectors
{
	TEST_CLASS(Vector4Test)
	{
	public:
		// Testing if all neccessary const:s are declared
		TEST_METHOD(V4_Const)
		{
		}

		TEST_METHOD(V4_Size)
		{
		}

		TEST_METHOD(V4_Default_Constructor)
		{
		}
		TEST_METHOD(V4_Constructor)
		{
		}

		// Compiler generated version as stated in the assignment description, test included for reference and completeness
		TEST_METHOD(V4_Copy_Constructor)
		{
		}

		// Compiler generated version as stated in the assignment description, test included for reference and completeness
		TEST_METHOD(V4_Assignment)
		{
		}

		TEST_METHOD(V4_ToTGAConvertion)
		{
		}

		TEST_METHOD(V4_ToOtherTypeConvertion)
		{
		}

		TEST_METHOD(V4_Negation)
		{
		}
		TEST_METHOD(V4_Addition)
		{
		}

		TEST_METHOD(V4_Subtraction)
		{
		}

		TEST_METHOD(V4_Scalar_Multiplication)
		{
		}

		TEST_METHOD(V4_Length)
		{
		}

		TEST_METHOD(V4_LengthSqrOptimize)
		{
		}

		TEST_METHOD(V4_Unit_Vector_Length)
		{
		}

		TEST_METHOD(V4_Normalise)
		{
		}

		TEST_METHOD(V4_Length_Zero_Vector)
		{
		}

		TEST_METHOD(V4_Normalise_Zero_Vector)
		{
		}

		TEST_METHOD(V4_Component_Multiplication)
		{
		}
		TEST_METHOD(V4_Dot)
		{
		}

	private:
		static const float ourToleranceF;
		static const double ourToleranceD;
	};

	const float Vector4Test::ourToleranceF = 0.00001f;
	const double Vector4Test::ourToleranceD = 0.00001;
}