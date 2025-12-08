#include "stdafx.h"
#include "CppUnitTest.h"
#include <type_traits>
#include <cmath>

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
		T x, y;

		Vector2() : x(T(0)), y(T(0))
		{
		}

		Vector2(const T aX, const T aY) : x(aX), y(aY)
		{
		}

		Vector2(const Vector2&) = default;
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
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Vector2f = CommonUtilities::Vector2<float>;
using Vector2d = CommonUtilities::Vector2<double>;
using Vector2i = CommonUtilities::Vector2<int>;

using TgaVectorf = Tga::Vector2<float>;
using TgaVectord = Tga::Vector2<double>;
using TgaVectori = Tga::Vector2<int>;

namespace Vectors
{
	TEST_CLASS(Vector2Test)
	{
	public:
		TEST_METHOD(V2_Const)
		{
			const Vector2f v{1.f, 2.f};
			const Vector2f u{2.f, 0.5f};

			auto len = v.Length();
			auto lensq = v.LengthSqr();
			auto dot = v.Dot(u);
			auto nrm = v.GetNormalized();
			auto tga = v.ToTga();
			auto castd = v.ToType<double>();
			(void)len;
			(void)lensq;
			(void)dot;
			(void)nrm;
			(void)tga;
			(void)castd;

			static_assert(std::is_copy_constructible_v<Vector2f>);
			static_assert(std::is_copy_assignable_v<Vector2f>);
			static_assert(std::is_trivially_destructible_v<Vector2f>);
		}

		TEST_METHOD(V2_Size)
		{
			Assert::AreEqual<size_t>(sizeof(Vector2f), sizeof(float) * size_t(2));
			Assert::AreEqual<size_t>(sizeof(Vector2d), sizeof(double) * size_t(2));
			Assert::AreEqual<size_t>(sizeof(Vector2i), sizeof(int) * size_t(2));
		}

		TEST_METHOD(V2_Default_Constructor)
		{
			Vector2f vf;
			Vector2i vi;
			Assert::AreEqual(0.f, vf.x);
			Assert::AreEqual(0.f, vf.y);
			Assert::AreEqual(0, vi.x);
			Assert::AreEqual(0, vi.y);
		}

		TEST_METHOD(V2_Constructor)
		{
			Vector2d v{1.0, -2.5};
			Assert::AreEqual(1.0, v.x);
			Assert::AreEqual(-2.5, v.y);
		}

		TEST_METHOD(V2_Copy_Constructor)
		{
			const Vector2f a{3.f, -2.f};
			Vector2f b{a};
			Assert::AreEqual(a.x, b.x);
			Assert::AreEqual(a.y, b.y);
		}

		TEST_METHOD(V2_Assignment)
		{
			const Vector2i a{1, 2};
			Vector2i b;
			b = a;
			Assert::AreEqual(1, b.x);
			Assert::AreEqual(2, b.y);
		}

		TEST_METHOD(V2_ToTGAConvertion)
		{
			const Vector2f v{1.f, 2.f};
			TgaVectorf t = v.ToTga();
			Assert::AreEqual(v.x, t.x);
			Assert::AreEqual(v.y, t.y);
		}

		TEST_METHOD(V2_ToOtherTypeConvertion)
		{
			const Vector2i vi{1, -2};
			auto vf = vi.ToType<float>();
			Assert::AreEqual(1.f, vf.x);
			Assert::AreEqual(-2.f, vf.y);

			const Vector2f vfx{1.5f, -2.25f};
			auto vd = vfx.ToType<double>();
			Assert::AreEqual(1.5, vd.x, ourToleranceD);
			Assert::AreEqual(-2.25, vd.y, ourToleranceD);
		}

		TEST_METHOD(V2_Negation)
		{
			const Vector2d v{1.0, -2.0};
			auto n = -v;
			Assert::AreEqual(-1.0, n.x);
			Assert::AreEqual(2.0, n.y);
		}

		TEST_METHOD(V2_Addition)
		{
			const Vector2f a{1.f, 2.f};
			const Vector2f b{-3.f, 5.f};
			auto c = a + b;
			Assert::AreEqual(-2.f, c.x);
			Assert::AreEqual(7.f, c.y);
		}

		TEST_METHOD(V2_Subtraction)
		{
			const Vector2i a{5, 7};
			const Vector2i b{3, -1};
			auto c = a - b;
			Assert::AreEqual(2, c.x);
			Assert::AreEqual(8, c.y);
		}

		TEST_METHOD(V2_Scalar_Multiplication)
		{
			const Vector2f v{1.f, -2.f};
			auto a = v * 2.f;
			auto b = 2.f * v;
			Assert::AreEqual(2.f, a.x);
			Assert::AreEqual(2.f, b.x);
			Assert::AreEqual(-4.f, a.y);
			Assert::AreEqual(-4.f, b.y);
		}

		TEST_METHOD(V2_Length)
		{
			const Vector2f v{3.f, 4.f}; // length = 5
			Assert::AreEqual(5.f, v.Length(), ourToleranceF);
		}

		TEST_METHOD(V2_LengthSqrOptimize)
		{
			const Vector2d v{2.0, -3.0}; // len^2 = 4 + 9 = 13
			Assert::AreEqual(13.0, v.LengthSqr(), ourToleranceD);
			Assert::AreEqual(v.Length() * v.Length(), v.LengthSqr(), ourToleranceD);
		}

		TEST_METHOD(V2_Unit_Vector_Length)
		{
			const Vector2f n{0.f, 1.f};
			Assert::AreEqual(1.f, n.Length(), ourToleranceF);
		}

		TEST_METHOD(V2_Normalise)
		{
			Vector2d v{3.0, 4.0};
			v.Normalize();
			Assert::AreEqual(0.6, v.x, ourToleranceD);
			Assert::AreEqual(0.8, v.y, ourToleranceD);
			Assert::AreEqual(1.0, v.Length(), ourToleranceD);

			const Vector2f u{1.f, 2.f}; // length = sqrt(5)
			const float inv = 1.0f / std::sqrt(5.0f);
			auto gn = u.GetNormalized();
			Assert::AreEqual(1.f * inv, gn.x, ourToleranceF);
			Assert::AreEqual(2.f * inv, gn.y, ourToleranceF);
			Assert::AreEqual(std::sqrt(5.f), u.Length(), ourToleranceF); // original unchanged
		}

		TEST_METHOD(V2_Length_Zero_Vector)
		{
			const Vector2f z{0.f, 0.f};
			Assert::AreEqual(0.f, z.Length(), ourToleranceF);
			Assert::AreEqual(0.f, z.LengthSqr(), ourToleranceF);
		}

		TEST_METHOD(V2_Normalise_Zero_Vector)
		{
			Vector2d z{0.0, 0.0};
			z.Normalize(); // should remain zero, no NaN
			Assert::AreEqual(0.0, z.x, ourToleranceD);
			Assert::AreEqual(0.0, z.y, ourToleranceD);

			auto gn = Vector2f{0.f, 0.f}.GetNormalized();
			Assert::AreEqual(0.f, gn.x, ourToleranceF);
			Assert::AreEqual(0.f, gn.y, ourToleranceF);
		}

		TEST_METHOD(V2_Component_Multiplication)
		{
			const Vector2i a{2, -3};
			const Vector2i b{-1, -2};
			auto c = a * b; // component-wise
			Assert::AreEqual(-2, c.x);
			Assert::AreEqual(6, c.y);
		}

		TEST_METHOD(V2_Dot)
		{
			const Vector2f a{1.f, 2.f};
			const Vector2f b{-2.f, 0.5f}; // dot = -2 + 1 = -1
			Assert::AreEqual(-1.f, a.Dot(b), ourToleranceF);
			Assert::AreEqual(a.LengthSqr(), a.Dot(a), ourToleranceF);
		}

	private:
		static const float ourToleranceF;
		static const double ourToleranceD;
	};

	const float Vector2Test::ourToleranceF = 0.00001f;
	const double Vector2Test::ourToleranceD = 0.00001;
} // namespace Vectors
