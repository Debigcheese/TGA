#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <chrono>

#include "Shared/Utility.h"
#include "Student Code/Vector3.h"

/// <summary>
/// This is a hack to emulate the TGA vector for the task of convertion
/// It only works because they happen to have the same name
/// </summary>
namespace Tga
{
	template<class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		Vector3() :x(T(0)), y(T(0)), z(T(0)) {}
		Vector3(const T aX, const T aY, const T aZ) :x(aX), y(aY), z(aZ) {}
	};
}

/// <summary>
/// To make the test-code cleaner we have a shorthand way to refer to the types
/// where the tga-vectors are prefixed Tga.
/// All the shorthands are post-fixed with the dimentionality as a number.
/// Along with the type as a one char shortened version, so for example it identifies:
/// float as 'f', int as 'i' or double as 'd'
/// </summary>
using TgaVector3f = Tga::Vector3<float>;
using TgaVector3d = Tga::Vector3<double>;
using TgaVector3i = Tga::Vector3<int>;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;
using Vector3i = CommonUtilities::Vector3<int>;

namespace Vectors
{
	TEST_CLASS(Vector3Test)
	{
	public:
		// Testing if all neccessary const:s are 
		// declared, This is a compile time test
		TEST_METHOD(V3_Const)
		{
		}
		TEST_METHOD(V3_Size)
		{
		}
		TEST_METHOD(V3_Default_Constructor)
		{
		}

		TEST_METHOD(V3_Constructor)
		{
		}

		// Compiler generated version as stated in the assignment description, test included for reference and completeness
		TEST_METHOD(V3_Copy_Constructor)
		{
		}

		// Compiler generated version as stated in the assignment description, test included for reference and completeness
		TEST_METHOD(V3_Assignment)
		{
		}

		TEST_METHOD(V3_ToTGAConvertion)
		{
		}

		TEST_METHOD(V3_ToOtherTypeConvertion)
		{
		}

		TEST_METHOD(V3_Negation)
		{
		}

		TEST_METHOD(V3_Addition)
		{
		}

		TEST_METHOD(V3_Subtraction)
		{
		}

		TEST_METHOD(V3_Scalar_Multiplication)
		{
		}

		TEST_METHOD(V3_Length)
		{
		}

		TEST_METHOD(V3_LengthSqrOptimize)
		{
		}

		TEST_METHOD(V3_Unit_Vector_Length)
		{
		}

		TEST_METHOD(V3_Normalise)
		{
		}

		TEST_METHOD(V3_Length_Zero_Vector)
		{
		}

		TEST_METHOD(V3_Normalise_Zero_Vector)
		{
		}

		TEST_METHOD(V3_Component_Multiplication)
		{
		}
		TEST_METHOD(V3_Dot)
		{
		}

		TEST_METHOD(V3_Cross)
		{
		}

	private:
		static const float ourToleranceF;
		static const double ourToleranceD;
	};

	const float Vector3Test::ourToleranceF = 0.00001f;
	const double Vector3Test::ourToleranceD = 0.00001;
}